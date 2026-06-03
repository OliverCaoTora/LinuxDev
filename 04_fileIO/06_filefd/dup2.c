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

    // read(fd_1, buf, 1);
    // read(fd_2, buf2, 1);
    // read(fd_3, buf3, 1);

    // // printf("data from fd_1: %c\n", buf[0]);
    // printf("data from fd_2: %c\n", buf2[0]);
    // printf("data from fd_3: %c\n", buf3[0]);

    while(1){
        sleep(5);
    }

    return 0;
}