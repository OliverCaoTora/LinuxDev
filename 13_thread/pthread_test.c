#include <stdio.h>
// pthread is .so
#include <pthread.h>
#include <unistd.h>

#include <string.h>

static void *my_thread_func(void *data)
{
    // while(1)
    // { 
    //     sleep(1); 
    // }
    printf("This is thread.\n");

    return NULL;
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

     pthread_detach(tid);

    ret = pthread_join(tid, NULL);
    if (ret != 0)
    {
        printf("pthread_join failed: %s\n", strerror(ret)); // pthread_join failed: Invalid argument
    }

    // while(1)
    // {
    //     sleep(1);
    // }

    return 0;
}
