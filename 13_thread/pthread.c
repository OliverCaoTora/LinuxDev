#include <stdio.h>
// pthread is .so
#include <pthread.h>
#include <unistd.h>

static void *my_thread_func(void *data)
{
    while(1)
    { 
        sleep(1); 
    }
}

int main(int argc, char **argv)
{
    pthread_t tid;
    int ret;

    ret = pthread_create(&tid, NULL, my_thread_func, NULL);
    
    if(ret)
    {
        printf("pthread_creat err!\n");
        return -1;
    }

    while(1)
    {
        sleep(1);
    }

    return 0;
}
