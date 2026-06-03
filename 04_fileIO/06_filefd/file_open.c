#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: %s <file>\n", argv[0]);
    }

    int fd_1 = open(argv[1], O_RDWR);
    close(fd_1);
    int fd_2 = open(argv[1], O_RDWR);

    printf("fd_1 = %d\n", fd_1);
    printf("fd_2 = %d\n", fd_2);

    return 0;
}