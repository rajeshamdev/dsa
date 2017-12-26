#include <bits/stdc++.h>
#include <pthread.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <strings.h>


using namespace std;

int mfscreate()
{
    int fsid = creat("/tmp/myfs", S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);

    for (int i = 0; i < 20; i++) {
        string fname ("file" + to_string(i));
        string binary = bitset<32>(fname.length()).to_string();
        ssize_t len = write(fsid, binary.c_str(), 32);
        len = write(fsid, fname.c_str(), fname.length());
    }

    close(fsid);
   
    fsid = open("/tmp/myfs", O_RDWR);
    for (int i = 0; i < 20; i++) { 
        char buf[100];
        int len = read(fsid, buf, 32);
        buf[32] = 0;
        string abc(buf);
        unsigned long decimal = std::bitset<32>(abc).to_ulong();
        std::cout<<"decimal: " << decimal<<"\n";

        len = read(fsid, buf, decimal);
        buf[decimal] = 0;
        cout << "fname: " << buf << "\n";
    }
    close(fsid);
    //return len;

}

int main(void)
{
//    mfscreate();
      int len = 8;
      cout << "lowest bit set: " << (len &(~(len-1))) << "\n";

    return 0;
}
