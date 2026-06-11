#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    int fd;
    int err;
    int len;
    unsigned char byte;
    struct input_id dev_id;
    unsigned int evbit[2];
    struct input_event event;

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

    if(argc < 2)
    {
        printf("Usage: %s <dev> [nonblock]\n", argv[0]);
        return -1;
    }
    if (argc == 3 && !strcmp(argv[2], "nonblock")){
        fd = open(argv[1], O_RDONLY | O_NONBLOCK);
    } 
    else 
    {
        fd = open(argv[1], O_RDONLY);
    }
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
        len = read(fd, &event, sizeof(event));
        if (len == sizeof(event))
        {
            printf("Get event: type = 0x%x, code = 0x%x, value = 0x%x\n", event.type, event.code, event.value);
        }
        else
        {
            printf("read err %d\n", len);
        }
        if (argc > 2 && !strcmp(argv[2], "nonblock"))
        {
            sleep(4);
        }
    }

    return 0;
}