#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> // file control flag, open
#include <errno.h>
#include <string.h>
#include <unistd.h> // System file IO - write close

int main(int argc, char **argv){
    int fd;
    int len;

    if (argc < 3)
    {
        printf("Usage: %s <file> <string1> <string2> ...\n", argv[0]);
        return -1;
    }

    fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
        printf("can not open file %s\n", argv[1]);
        printf("errno = %d\n", errno);
        printf("err: %s\n", strerror(errno));
        perror("open");
    }
    else{
        printf("fd = %d\n", fd);
    }

    for(int i = 2; i<argc; i++)
    {
        len = write(fd, argv[i], strlen(argv[i]));
        if(len != strlen(argv[i])){
            perror("write");
            break;
        }
        write(fd, "\r\n", 2);
    }



    return 0;
}