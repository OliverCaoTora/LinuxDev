#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    unsigned char buf[10];
    // unsigned char buf2[10];
    // unsigned char buf3[10];

    if (argc != 2)
    {
        printf("Usage: %s <file>\n", argv[0]);
    }

    int fd_1 = open(argv[1], O_RDWR, 0777);
    // close(fd_1);
    // int fd_2 = open(argv[1], O_RDWR);

    // int fd_3 = dup(fd_1); // new fd, but point to same file struct

    // if(fd_1 <0 || fd_2 < 0 || fd_3 < 0)
    if(fd_1 <0)
    {
        printf("Can not open file: %s", argv[1]);
        return -1;
    }

    printf("fd_1 = %d\n", fd_1);
    // printf("fd_2 = %d\n", fd_2);

    dup2(fd_1, 1); // relocated 1 to fd_1
    printf("hello, world\n"); // printf default output to 1
    // That mean now printf will print direct to fd_1

    while(1){
        sleep(5);
    }

    return 0;
}