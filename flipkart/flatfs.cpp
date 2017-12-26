
/* Compiled on Ubunto 16.04: g++ -g -std=c++11 flatfs.cpp -lpthread */

#include <bits/stdc++.h>
#include <pthread.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


using namespace std;


/**
 *  Design sketch:
 *  
 *  Filesystem layout:
 * -------------------------------
 * |100 bytes for FS header      |
 * |----------------------------
 * |5fileA3Raj7Krishna8FlipKart  |
 * |.....                        |
 * |                             |
 * -------------------------------
 * | 512 byte data blocks        |
 * |                             |
 * |                             |
 * |            Data blocks      |
 * |                             |
 * |                             |
 * |                             |
 * -------------------------------
 *
 * In the filesystem Meta:
 *  1) First 100 bytes is reserved for filesystem header (not yet defined).
 *  2) For each file : we store <file name len, file name>. Filename len is
 *     is assumed to fit in 32-bit - and this len is stored in binary
 *     bit format for easy read (for instance, we just need to read 32-bits
 *     (4 bytes) to know the file name len, then, we just need to read that
 *     len bytes to know the file name and so on.
 *     See example : 5fileA3Raj7Krishna8FlipKart.
 *     In this example, 5 (is stored in binary format). That indicates the len of "FileA".
 *     Then, "3Raj", "7Krishna", "8FlipKart" and so on.
 * 
 *  3) Data blocks are assumed to be of len 512 bytes (and multiple size not supported).
 *  
 * Inode allocation: For now I assumed it to be integeri range (4B len). This starts from 1
 *      and increases monotonically. Efficient way would be bit map representation (not implemented).
 *
 * Data block allocation: number of data blocks is calculated as:
 *    totalFSBlocks = (fsSize - metaSize) / fsblock;
 *    This is also allocated in monotonically increasing order for simplicity. Efficient
 *    way would be bit map representation.
 *
 * Inode cache: When the file system mounts, we like to read the all the file names and cache them.
 *   Since this is flat file system, we like to avoid to many disk accesses. For this reason, we
 *   like to cache the inodes.
 *
 * create/open: These calls are almost same. When we create/open a file, we look up in cache,
 *   if its already in the cache, we dont let duplicate namespace (or open).
 *
 * write: On the same flat file (which was created during file system mount), we allocate
 *   data blocks for each write call and write into that block.
 *
 * Note: Neither inodes or data blocks reclaimed (for now).
 *
 * 
 */

// super block info. Assume the size is 10MB.
const ulong metaSize = 10*1024*1024UL;

// total file system size. Assume supported size 5GB.
const ulong fsSize = 5*1024*1024*1025UL;

// start with small data blocks. Multiple blocks size not supported yet.
const ushort fsblock = 512;

// We let writes upto this many data blocks. After this, FS is full.
const ulong totalFSBlocks = (fsSize - metaSize) / fsblock;

// This tracks filesystem meta data offset (this is not persistent).
const int HEADER_START = 100;
int trackMetaOffset;

// Allocation of inode numbers and data block numbers could
// be well/efficiently done with bitmap vector (or such). Lacking
// time, I am devising simple allocation. Each time an inode numer
// or data block number needed, we increase the below counter monotonically
// under a lock protection.
uint lastUsedInodeNum = 0;
pthread_mutex_t inumLock;
uint lastUsedDataBlock = 0;
pthread_mutex_t dataBlockLock;

/*
 * FS specific.
 */
int fsid;
pthread_mutex_t fslock;
unordered_set<string> fsFileMap; // filename lookup cache to avoid disk access.
int mfscreate();

// File specific.
//TBD: create a another mutex to support parallel writes on filesystem.
unordered_set<int> fdCache; // fd lookup cache to avoid expensive disk access.
int mcreate(const string &pathname);
int mopen(const string &pathname, int flags);
ssize_t mwrite(int fd);
int mclose(int fd);
//int mseek(); // TBD

int allocInode(void)
{
    pthread_mutex_lock(&inumLock);
    int inum = ++lastUsedInodeNum;
    pthread_mutex_unlock(&inumLock);
    return inum;
}

int allocDataBlock(void)
{
    pthread_mutex_lock(&dataBlockLock);
    int dataBlockNum = ++lastUsedDataBlock;
    pthread_mutex_unlock(&dataBlockLock);
    return dataBlockNum;
}

int mfscreate()
{
    // let this file open as long as machine alive.
    // Data is lost after machine reboot - assume that is OK for now.
    fsid = creat("/tmp/myfs", S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
    if (fsid == -1) {
        cout << "Creating meta file failed : " << errno << "\n";
        int rc = -errno;
        return rc;
    }

    if (pthread_mutex_init(&fslock, NULL) != 0)
    {
        cout << "fsLock mutex init failed\n";
        int rc = -errno;
        return rc; // TBD: on error, remove the /tmp/myfs file.
    }
    if (pthread_mutex_init(&inumLock, NULL) != 0)
    {
        cout << "inum mutex init failed\n";
        int rc = -errno;
        return rc; // TBD: on error, remove the /tmp/myfs file.
    }

    if (pthread_mutex_init(&dataBlockLock, NULL) != 0)
    {
        cout << "dataBlockLock mutex init failed\n";
        int rc = -errno;
        return rc; // TBD: on error, remove the /tmp/myfs file.
    }

    trackMetaOffset = HEADER_START;

    // TBD: populate existing file names into fdCache.
    return 0;
}

int mcreate(const string &fname)
{
    int fd = mopen(fname, O_CREAT|O_WRONLY);
    return fd;
}

// create and open calls almost behaves similar in this specfic filesystem.
// Both of them allow write only ops. Based on this, to simplify the logic,
// don't let concurrent open calls on same file.
int mopen(const string &fname, int flags)
{
    pthread_mutex_lock(&fslock); // check for error code.
    // fail if file already opened.
    if (fsFileMap.find(fname) != fsFileMap.end()) {
        cout << "File exists or opened: " << fname << "\n";
        pthread_mutex_unlock(&fslock);
        return -1;
    }
    int fd = allocInode();
    fdCache.insert(fd);

    lseek(fsid, trackMetaOffset, SEEK_CUR);
    string fileNameLenInBinary = bitset<32>(fname.length()).to_string();
    ssize_t len = write(fsid, fileNameLenInBinary.c_str(), 32); // write filename len
    trackMetaOffset += len; 
    len = write(fsid, fname.c_str(), fname.length()); // write file name
    trackMetaOffset += len; 

    pthread_mutex_unlock(&fslock); // check for error code.

    return fd;
}

// Imp Note: Data block allocation to a file is not being tracked, as
// we dont read the file. The focus is mainly on writes only.
// How ever, the design indeed takes care of writes not over stepping
// on data blocks.
ssize_t mwrite(int fd, const void *buf, size_t count)
{
    if (!count) return 0;

    int dataBlocksReqd = count/fsblock;
    if (!dataBlocksReqd) {
        // We need just one data block here.
        ++dataBlocksReqd;
    } else if ((count - dataBlocksReqd*fsblock) > fsblock) { // TBD: handle integer overflow
        ++dataBlocksReqd;
    }
    ssize_t runningLen = 0;
    for (int i = 1; i <= dataBlocksReqd; i++) {
        int dataBlock = allocDataBlock();
        // Note: 'seek' is must here because, data block
        // allocation may not be contiguous under multiple writers
        // in filesystem. This is inefficient, but works. At the same
        // I know path forward for effient solution, but lacking time,
        // I am devising the simple approach for now.
        if (dataBlock < 2) {
            // data is being written to the very first data block,
            // we need to write right after metaSize.
            lseek(fsid, metaSize, SEEK_CUR);
        } else {
            // otherwise, we need to write after so far written blocks.
            lseek(fsid, metaSize+(dataBlock -1)*fsblock, SEEK_CUR);
        }
        ssize_t len = write(fsid, (char*)buf+runningLen, fsblock);
        runningLen += len;
    }

    return runningLen;
}

int mclose(int fd)
{
    pthread_mutex_lock(&fslock);
    auto it = fdCache.find(fd);
    fdCache.erase(it);
    pthread_mutex_unlock(&fslock);
    return 0;

}

/* not yet completed */
void* fstest1(void *arg)
{
    int opscount = 10;
    while (opscount--) {
        string fname = "fileA" + string("rand() % 10 + 1");
        int fd = mcreate(fname); // check for error.
    }
}

/* not yet completed */
void* fstest2(void *arg)
{
    int opscount = 10;
    while (opscount--) {
        string fname = "fileB" + string("rand() % 10 + 1");
        int fd = mcreate(fname); // check for error.
    }
}

int main(void)
{
    mfscreate();
    pthread_t thread1, thread2;
    pthread_create (&thread1, NULL, fstest1, NULL);
    pthread_create (&thread2, NULL, fstest2, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}
