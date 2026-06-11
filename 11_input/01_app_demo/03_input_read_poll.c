#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <string.h>
#include <unistd.h>
#include <poll.h>

int main(int argc, char** argv)
{
    int fd;
    int err;
    int len;
    int ret;
    unsigned char byte;
    struct input_id dev_id;
    unsigned int evbit[2];
    struct input_event event;
    struct pollfd fds[1];
    nfds_t nfds = 1;

    char *ev_names[] = {
		"EV_SYN ",
		"EV_KEY ",
		"EV_REL ",
		"EV_ABS ",
		"EV_MSC ",
		"EV_SW	",
		"NULL ",
		"NULL ",
		"NULL ",
		"NULL ",
		"NULL ",
		"NULL ",
		"NULL ",
		"NULL ",
		"NULL ",
		"NULL ",
		"NULL ",
		"EV_LED ",
		"EV_SND ",
		"NULL ",
		"EV_REP ",
		"EV_FF	",
		"EV_PWR ",
		};

    if(argc != 2)
    {
        printf("Usage: %s <dev>\n", argv[0]);
        return -1;
    }
    fd = open(argv[1], O_RDONLY | O_NONBLOCK);
    if(fd < 0)
    {
        printf("open %s error\n", argv[1]);
        return -1;
    }
    err = ioctl(fd, EVIOCGID, &dev_id);
    if (err == 0)
    {
        printf("bustype = 0x%x\n", dev_id.bustype);
        printf("vendor = 0x%x\n", dev_id.vendor);
        printf("product = 0x%x\n", dev_id.product);
        printf("version = 0x%x\n", dev_id.version);

    }

    len = ioctl(fd, EVIOCGBIT(0, sizeof(evbit)), &evbit);
    if(len>0 && len <=sizeof(evbit))
    {
        for (int i = 0; i < len; i++)
        {
            byte = ((unsigned char *)evbit)[i];
            for (int bit = 0; bit < 8; bit++)
            {
                if (byte & (1<<bit))
                {
                    printf("%s ", ev_names[i *8+bit]);
                }
            }
        }
        printf("\n");
    }

    while (1)
    {
        fds[0].fd= fd;
        fds[0].events = POLLIN;
        fds[0].revents = 0;
        ret = poll(fds, nfds, 5000);
        if (ret > 0)
        {
            if (fds[0].revents & POLLIN)
            {

                // len = read(fd, &event, sizeof(event));
                // if (len == sizeof(event))
                // {
                //     printf("Get event: type = 0x%x, code = 0x%x, value = 0x%x\n", event.type, event.code, event.value);
                // }
                while (read(fd, &event, sizeof(event)) == sizeof(event))
                {
                    printf("Get event: type = 0x%x, code = 0x%x, value = 0x%x\n", event.type, event.code, event.value);
                }

                /*注意这里，if虽然和while有同样的结果，但是实现机制不一样*/
                /*poll的原理是只要缓存区是有数据可以读，就立即返回*/
                /*所以即使是if，那流程就是
                    poll -> read 第1条
                    poll -> read 第2条
                    poll -> read 第3条
                    poll -> read 第4条
                    poll -> read 第5条
                    poll -> read 第6条
                    poll -> read 第7条
                */
               /*而while的机制是
                    poll 等待有数据
                    read 第1条
                    read 第2条
                    read 第3条
                    read 第4条
                    ...
                    直到没有数据
                    回到外层 poll
               */
              /*同时注意内圈while使用非阻塞read*/
            }
        }
        else if (ret == 0)
        {
            printf("time out\n");
        }
        else
        {
            printf("read err %d\n", len);
        }
      
    }

    return 0;
}