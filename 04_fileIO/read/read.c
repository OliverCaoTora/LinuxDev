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
    char buf[100];
    if (argc != 2)
    {
        printf("Usage: %s <file>\n", argv[0]);
        return -1;
    }

    fd = open(argv[1], O_RDWR, 0644);
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


    while (1){
        len = read(fd, buf, sizeof(buf)-1);
        if (len < 0)
        {
            perror("read");
            close(fd);
            return -1;
        }
        else if(len == 0){
            break;
        }
        else {
            buf[len-1] = '\0';
            printf("%s", buf);
        }
    }

    return 0;
}