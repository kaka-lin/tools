#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/statvfs.h>
#include "args.h"

// statvfs
//
// the prototype of the statvfs is:
// 
//     int statvfs(const char *path, struct statvfs *buf);
// 
// The results will be filled to the buf statvfs struct:
// 
//     struct statvfs {
//         unsigned long  f_bsize;    // filesystem block size
//         unsigned long  f_frsize;   // fragment size
//         fsblkcnt_t     f_blocks;   // size of fs in f_frsize units
//         fsblkcnt_t     f_bfree;    // # free blocks
//         fsblkcnt_t     f_bavail;   // # free blocks for unprivileged users
//         fsfilcnt_t     f_files;    // # inodes
//         fsfilcnt_t     f_ffree;    // # free inodes
//         fsfilcnt_t     f_favail;   // # free inodes for unprivileged users
//         unsigned long  f_fsid;     // filesystem ID
//         unsigned long  f_flag;     // mount flags
//         unsigned long  f_namemax;  // maximum filename length
//     };

uint64_t get_available_space(const char *path)
{
  struct statvfs stat;
  
  if (statvfs(path, &stat) != 0) {
    // error happens, just quits here
    return -1;
  }

  // the available size is f_bsize * f_bavail
  return (stat.f_bsize * stat.f_bavail) / 1024; // KB
}

int main(int argc, char **argv)
{  
    int ret;
    uint64_t filespace;
    char *path = "/dev";

    ret = parse_args(&path, argc, argv);
    if (ret)
        return 1;    

    filespace = get_available_space(path);
    printf("Available space under `%s`: %luKB.\n", 
        path, filespace);

    return 0;
}
