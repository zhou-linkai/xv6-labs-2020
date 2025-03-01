#ifndef _SYSINFO_H_
#define _SYSINFO_H_

#include "types.h"

// 定义 sysinfo 结构体
struct sysinfo {
    uint64 freemem;   // 系统中剩余的空闲内存 (单位：字节)
    uint64 nproc;     // 系统中当前正在运行的进程数量
};

#endif // _SYSINFO_H_

