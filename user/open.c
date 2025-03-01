#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"
// create a file , write to it 
int 
main()
{
    int fd = open("output.txt", O_WRONLY | O_CREATE);
    write(fd, "ooo\n", 4);

    exit(0);
}
