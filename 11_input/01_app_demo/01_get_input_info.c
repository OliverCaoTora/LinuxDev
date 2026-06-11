#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/ioctl.h>

int main(int argc, char** argv)
{
    int fd;
    int err;
    int len;
    unsigned char byte;
    struct input_id dev_id;
    unsigned int evbit[2];
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
        printf("Usage: %s <dev >\n", argv[0]);
        return -1;
    }
    fd = open(argv[1], O_RDONLY);
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
    return 0;
}