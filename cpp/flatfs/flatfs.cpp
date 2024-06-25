
/* compiled on Ubuntu 16.04: g++ -g -std=c++11 flatfs.cpp */

#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

/* persistent inode structure */
class Inode {
private:
    const ushort DATA_BLOCKS_PER_INODE = 251; 
public:
    char fname[8]; // file name, 8 chars max
    uint inum;     // inode number. usefule for caching reasons.
    uint numOfDataBlocks; // number of data blocks allocated for a file
    uint fileSize; // real file size. Sparse files not supported
    unique_ptr<uint[]> dataBlocks; // array of data blocks for inode.
    Inode(void) {
        numOfDataBlocks = 0, fileSize = 0;
        dataBlocks = unique_ptr<uint[]>(new uint[DATA_BLOCKS_PER_INODE]);
    }
    ~Inode() { }
};

/* super block for the filesystem */
class SuperBlock {
public:
    uint numOfDataBlocks; // Total data blocks in the file system
    uint numOfInodes; // Total number of inodes in the filesystem
    uint iTableStartOffset; // Inode table location
    uint dTableStartOffset; // datablocks table location
    string magicStr; // IDLI
    SuperBlock(const uint &blocks, const uint &inodes, const uint &itable,
        const uint &dtable) :
        numOfDataBlocks(blocks), numOfInodes(inodes),
        iTableStartOffset(itable), dTableStartOffset(dtable)
    {
        magicStr = "IDLI";
    }
    ~SuperBlock() { }
};

class flatFS {
private:
    const uint DATA_BLOCK_SIZE = 4096; // support only 4K for now.
    const ushort BLOCKS_FOR_SUPERBLOCK = 1; // one block for superblock
    const ushort BLOCKS_FOR_IMAP = 1; // reserver one block for inode bitmap.
    const ushort BLOCKS_FOR_DMAP = 1; // reserver 8 blocks for data blocks bitmap
    const ushort BLOCKS_FOR_ITABLE = 256; // blocks reserved for inode table.
    const ushort MAX_INODES = 1024;
    const ushort WORD_SIZE = 32;
    const ushort BITS_IN_WORD = 5;
    const ushort BITS_IN_INODEBITMAP = 1024;
    const uint   BITS_IN_DATABLOCKBITMAP = (256*1024);
    int flatFSfd;
    string flatFSName;
    ulong fsSize;
    unique_ptr<SuperBlock> superBlock;
    unique_ptr<Inode> inode;
    unordered_set<string> fnameCache;
    unordered_set<uint> iCache;
    unordered_map<string, uint> fnameMap;
    int *inodeBitMap;
    int *dataBlocksBitMap;

    inline void setInodeBitMap(const int &pos);
    inline bool isInodeInUse(const int &pos);
    int allocInode(void);
    void releaseInode(const int &pos); // returns -1 when when all inodes used
    inline void setDataBlockBitMap(const int &pos);
    inline bool isDataBlockInUse(const int &pos);
    int allocDataBlock(void); // returns -1 when all data blocks used, thus declaring filesystem out of space.
    void releaseDataBlock(const int &pos); // alloc data blocks and tries best to maintain data locality
    int syncMeta(void); // file meta to disk.
    int LoadMeta(void);

public:
    flatFS(const string &fsName, const ulong &size);
    ~flatFS(void);
    int Create(const string &fname);
    int Write(const int &fd, const string &buf);
    int Read(const string &fname);
    int Close(const int &fd);
    int Delete(const string &fname);
    int Update(const string &fname, const int &offset, const string &buf);
    void ListFiles(void);
};

flatFS::~flatFS(void)
{
    syncMeta();
    close(flatFSfd);
    delete[] inodeBitMap;
    delete[] dataBlocksBitMap;

}
// For now, meta data synced during the filesytem unmount.
// TBD: Need to sync periodically or event based.
int flatFS::syncMeta(void)
{
    auto inodeMapStartOffset = BLOCKS_FOR_SUPERBLOCK * DATA_BLOCK_SIZE - 1;
    pwrite(flatFSfd, (void*) inodeBitMap, 128, inodeMapStartOffset);
    auto dataMapStartOffset = (BLOCKS_FOR_SUPERBLOCK + BLOCKS_FOR_IMAP) * DATA_BLOCK_SIZE - 1;
    pwrite(flatFSfd, (void*) dataBlocksBitMap, 32768, inodeMapStartOffset);
}

int flatFS::LoadMeta(void)
{
    auto inodeMapStartOffset = BLOCKS_FOR_SUPERBLOCK * DATA_BLOCK_SIZE - 1;
    pread(flatFSfd, (void*) inodeBitMap, 128, inodeMapStartOffset);
    auto dataMapStartOffset = (BLOCKS_FOR_SUPERBLOCK + BLOCKS_FOR_IMAP) * DATA_BLOCK_SIZE - 1;
    pread(flatFSfd, (void*) dataBlocksBitMap, 32768, inodeMapStartOffset);
}

// Populate the super block info.
// Format/create/mount filesystem.
// Populate caches with ondisk info
flatFS::flatFS(const string &fsName, const ulong &size) : flatFSName(fsName), fsSize(size)
{
    auto blocksCnt   = fsSize/DATA_BLOCK_SIZE;
    auto inodesCnt       = (DATA_BLOCK_SIZE/sizeof(Inode)) * BLOCKS_FOR_ITABLE;
    auto iTableIndex = (BLOCKS_FOR_SUPERBLOCK + BLOCKS_FOR_IMAP +
                        BLOCKS_FOR_DMAP)  * DATA_BLOCK_SIZE - 1;
    auto dTableIndex = iTableIndex + BLOCKS_FOR_ITABLE * DATA_BLOCK_SIZE;

    superBlock = unique_ptr<SuperBlock>(new (nothrow) SuperBlock(blocksCnt,
                    inodesCnt, iTableIndex, dTableIndex));
    if (superBlock == nullptr) {
        cout << "Mem alloc failed for superBlock\n";
        exit(-ENOMEM);
    }

    // we need 1024 bits. With word size of 32, there are 32 buckets.
    inodeBitMap = new (nothrow) int[BITS_IN_INODEBITMAP/WORD_SIZE]; // 128 bytes.
    if (inodeBitMap == nullptr) {
        cout << "Mem alloc failed for inodeBitMap \n";
        exit(-ENOMEM);
    }

    // 1024 files each needs 256 blocks, so we need 1024*256=262144 bits or 32KB.
    dataBlocksBitMap = new (nothrow) int[BITS_IN_DATABLOCKBITMAP/WORD_SIZE];
    if (dataBlocksBitMap == nullptr) {
        cout << "Mem alloc failed for dataBlocksBitMap \n";
        delete[] inodeBitMap;
        exit(-ENOMEM);
    }
    
    // if the filesystem was there, just mount.
    // Otherwise format, create and mount.
    auto ret = access(fsName.c_str(), F_OK);
    if (!ret) {
        flatFSfd = open(fsName.c_str(), O_RDWR);
        if (flatFSfd == -1) {
            cout << "File system failed to mount, errno: " << errno << "\n";
            delete[] inodeBitMap;
            delete[] dataBlocksBitMap;
            exit(-errno);
        }
    } else {
        flatFSfd = open(fsName.c_str(), O_CREAT|O_RDWR);
        if (flatFSfd == -1) {
            cout << "File system failed to mount, errno: " << errno << "\n";
            delete[] inodeBitMap;
            delete[] dataBlocksBitMap;
            exit(-errno);
        }
        // format filesystem
        if (ftruncate(flatFSfd, fsSize) == -1) {
            close(flatFSfd);
            cout << "File system failed to mount, errno: " << errno << "\n";
            delete[] inodeBitMap;
            delete[] dataBlocksBitMap;
            exit(-errno);
        }
    }
    char buf1[8], buf2[8];
    cout << "Populating iCache, fnameCache and fnameMap with ondisk info : \n";
    for (int i = 0; i < MAX_INODES; i++) {
        uint inodeLocation = superBlock->iTableStartOffset + i*1024;
        pread(flatFSfd, (void*) buf1, 8, inodeLocation); // read inum
        pread(flatFSfd, (void*) buf2, 8, inodeLocation+10); // read fname
        if (buf1[0] != '\0' && buf2[0] != '\0') {
            auto inum = atoi(buf1);
            if (iCache.find(inum) == iCache.end()) {
                iCache.insert(inum);
            }
            string fname (buf2);
            if (fnameCache.find(fname) == fnameCache.end()) {
                fnameCache.insert(fname);
            }
            fnameMap.insert({fname, inum});
            cout << "\t inum: " << inum << ", fname: " << fname << "\n";
        }
    }
    cout << "\n";
    LoadMeta();
}

inline void flatFS::setInodeBitMap(const int &pos)
{
    inodeBitMap[pos >> BITS_IN_WORD] |= (1 << (pos % WORD_SIZE));
}

inline bool flatFS::isInodeInUse(const int &pos)
{
    return (inodeBitMap[pos >> BITS_IN_WORD] & (1 << (pos % WORD_SIZE)));
}

int flatFS::allocInode(void)
{
    for (int i = 0; i < BITS_IN_INODEBITMAP; i++) {
        if (!isInodeInUse(i)) {
            setInodeBitMap(i);
            return ++i;
        }
    }
    return -1; // all inodes used.
}

inline void flatFS::releaseInode(const int &pos)
{
    inodeBitMap[pos >> BITS_IN_WORD] &= ~(1 << (pos % WORD_SIZE));
}

inline void flatFS::setDataBlockBitMap(const int &pos)
{
    dataBlocksBitMap[pos >> BITS_IN_WORD] |= (1 << (pos % WORD_SIZE));
}

inline bool flatFS::isDataBlockInUse(const int &pos)
{
    return (dataBlocksBitMap[pos >> BITS_IN_WORD] & (1 << (pos % WORD_SIZE)));
}

int flatFS::allocDataBlock(void)
{
    // alloc data blocks in sequence for better data locality (hence better perf).
    for (int i = 0; i < BITS_IN_DATABLOCKBITMAP; i++) {
        if (!isDataBlockInUse(i)) {
            setDataBlockBitMap(i);
            return ++i;
        }
    }
    return -1; // all data blocks used. File system is full.
}

void flatFS::releaseDataBlock(const int &pos)
{
    dataBlocksBitMap[pos >> BITS_IN_WORD] &= ~(1 << (pos % WORD_SIZE));
}

int flatFS::Delete(const string &fname)
{
    auto iter = fnameCache.find(fname);
    if (iter == fnameCache.end()) {
        cout << fname << ": file does not exists\n";
        return -ENOENT;
    }
    // Release inode, data blocks etc.
    auto inum = fnameMap[fname];
    auto a = inum-1;
    releaseInode(a);
    char buf[10];
    auto inodeLocation = superBlock->iTableStartOffset  + (inum - 1) * DATA_BLOCK_SIZE;
    pread(flatFSfd, (void*) buf, 10, inodeLocation+20);
    auto dataBlocks = atoi(buf);
    for (int i = 0; i < dataBlocks; i++) {
        pread(flatFSfd, (void*) buf, 10, inodeLocation+40+i*10);
        auto dataBlockNum = atoi(buf);
        auto b = dataBlockNum - 1;
        releaseDataBlock(b);
    }

    iCache.erase(fnameMap[fname]);
    fnameMap.erase(fname);
    fnameCache.erase(iter);
    return 0;
}

void flatFS::ListFiles(void)
{
    cout << "Listing available files\n";
    for (const string &name : fnameCache) {
        cout << "\t" << name << "\n";
    }
}

// TDB: Read needs to copy data to user buffer.
// currently it dumps to stdout.
int flatFS::Read(const string &fname)
{
    auto len = fname.length();
    if (len == 0 || len > 8) return -EINVAL;

    auto iter = fnameMap.find(fname);
    if (iter == fnameMap.end()) {
        return -EINVAL;
    }
    auto inum = fnameMap[fname];

    cout << "Reading file, " << fname << "\n";
    string tmpstr;
    char *buf = new (nothrow) char[DATA_BLOCK_SIZE];
    if (!buf) {
        cout << "Read(): memory allocation failed for buf\n";
        return -ENOMEM;
    }
    auto inodeLocation = superBlock->iTableStartOffset  + (inum - 1) * DATA_BLOCK_SIZE;
    pread(flatFSfd, (void*) buf, 10, inodeLocation);
    cout << "\t inum: "<< buf << "\n";
  
    pread(flatFSfd, (void*) buf, 10, inodeLocation+10);
    cout << "\t fname: " << buf << "\n";
    
    pread(flatFSfd, (void*) buf, 10, inodeLocation+20);
    int dataBlocks = atoi(buf);
    cout << "\t Num of data blocks: " << dataBlocks << "\n";

    pread(flatFSfd, (void*) buf, 10, inodeLocation+30);
    cout << "\t file size: " << buf << "\n";
    
    for (int i = 0; i < dataBlocks; i++) {
        pread(flatFSfd, (void*) buf, 10, inodeLocation+40+i*10);
        cout << "\t Block num: " << buf << "\n";
        auto dataBlockNum = atoi(buf);
        auto dataBlockOffset = superBlock->dTableStartOffset +(dataBlockNum-1)*DATA_BLOCK_SIZE;
        pread(flatFSfd, (void*) buf, DATA_BLOCK_SIZE, dataBlockOffset);
        cout << "Data: " << buf << "\n";
    }
    delete[] buf;
    return 0;

}

int flatFS::Close(const int &fd)
{
    if (iCache.find(fd) == iCache.end()) return -EINVAL; // check stale fd.

    string tmpstr;

    // Update number of data blocks for this file.
    uint inodeLocation = superBlock->iTableStartOffset  + (fd - 1) * DATA_BLOCK_SIZE;
    tmpstr = to_string(inode->numOfDataBlocks);
    auto len = tmpstr.length();
    if (len < 10) tmpstr += '\0';
    pwrite(flatFSfd, (void*) tmpstr.c_str(), 10, inodeLocation+20); // update number of blocks
  
    // update file size. 
    tmpstr.clear();
    tmpstr = to_string(inode->fileSize);
    len = tmpstr.length();
    if (len < 10) tmpstr += '\0';
    pwrite(flatFSfd, (void*) tmpstr.c_str(), 10, inodeLocation+30);
    
    // update block number.
    for (int i = 0; i < inode->numOfDataBlocks; i++) {
        tmpstr.clear();
        tmpstr = to_string(inode->dataBlocks[i]);
        len = tmpstr.length();
        if (len < 10) tmpstr += '\0';
        pwrite(flatFSfd, (void*) tmpstr.c_str(), 10, inodeLocation+40+i*10);
    }
    return 0;
}

int flatFS::Create(const string &fname)
{
    auto len = fname.length();
    if (len == 0 || len > 8) {
        cout << "file name length must be between [1, 8] \n";
        return -EINVAL;
    }
    if (fnameCache.find(fname) != fnameCache.end()) {
        cout << "Creating duplicate file names not allowed \n";
        return -EEXIST;
    } else {
        fnameCache.insert(fname);
    }
    auto inum = allocInode();
    if (inum == -1) {
        cout << "Max allowed files reached, allowed limit" << MAX_INODES << "\n";
        fnameCache.erase(fname);
        return -ENFILE;
    }

    // Persist inode number and file name in on-disk inode.
    auto inodeLocation = superBlock->iTableStartOffset + (inum-1)*DATA_BLOCK_SIZE;
    string tmpstr = to_string(inum);
    len = tmpstr.length();
    if (len < 10) tmpstr += '\0';
    pwrite(flatFSfd, (void*) tmpstr.c_str(), 10, inodeLocation);
    pwrite(flatFSfd, (void*) fname.c_str(), 10, inodeLocation+10);

    fnameMap.insert({fname, inum});
    iCache.insert(inum);
    fnameCache.insert(fname);
  
    inode.reset(new Inode);
    return inum;
}

int flatFS::Write(const int &fd, const string &buf)
{
    if (iCache.find(fd) == iCache.end()) return -EINVAL; // check stale fd.
    auto len = buf.length();
    if (len == 0) return 0;

    auto dataBlockNum = allocDataBlock();
    if (dataBlockNum == -1) {
        cout << "Out of data blocks, disk quota exceeded\n";
        return -ENOSPC;
    }

    // limitation: cannot handle is write len greater than 4K.
    auto dataBlockOffset = superBlock->dTableStartOffset + (dataBlockNum - 1) * DATA_BLOCK_SIZE;
    auto written = pwrite(flatFSfd, buf.c_str(), len, dataBlockOffset);
    if (written != len) {
        cout << "Partial write \n";
        return written;
    }
    // inode info will be cached here until all writes are
    // completed to avoid too many disk accesses. And it
    // will be pushed to disk in Close call.
    inode->fileSize += written;;
    inode->dataBlocks[(inode->numOfDataBlocks)++] = dataBlockNum;
    len -= written;
    return 0;
}

int main(void)
{
    flatFS myFS("./myfs", 1024*1024*1024UL);

    int i = 0;
    while (i < 15) {
        ++i;
        string fname ("file" + to_string(i));
        int fd = myFS.Create(fname);
        cout << fname << ": " << fd << "\n";
        string wstr = "This is coding exercise. tbsifflsngfljgllgj;lsjg;jg;jgl;jg";
            wstr += "ljgljelg;lejmg;lg;leglgleg;lglgjlglg;ljg;lwg;lwjglerjgwglggj";
            wstr += "sshfkhgwhflwehglwehfwehfiwehfwehfiwehfehfiwehlwehflwehflwehfl";
            wstr += "wefwi8ryhfsdnvsdfklskfpwkdsbfvqeo[pold;lqvwnfe";
            wstr += "I am testing akjflajf;of coamdkhvwjfqu akwtfhuwtflksf  ";
            wstr += "sfhskv/.svkljshdlwkd.ska,,kadkajdlwadjlaflfmamfamf";

        myFS.Write(fd, wstr);
        myFS.Close(fd);
        myFS.Read(fname);
    }

    myFS.ListFiles();

    myFS.Delete("file2");
    myFS.ListFiles();
}
