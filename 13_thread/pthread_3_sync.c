#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include <semaphore.h>

static char g_buf[1000];

// static int g_hasData = 0;

static sem_t g_sem;

static void *my_thread_func(void *data)
{
    while(1)
    { 
        // sleep(1); 
        // while(g_hasData == 0);
        sem_wait(&g_sem);
        printf("revc: %s\n", g_buf);
    }

    /* 线程函数返回的是一个 void *，也就是一个指针值。这个指针指向的对象，在主线程通过 pthread_join() 取到并使用时，必须仍然有效。
        return NULL;          // 不返回有效数据
        
        return &global_var;   // 全局变量地址，可以
        
        static int result;
        return &result;       // static 变量地址，可以
        
        int *p = malloc(sizeof(int));
        *p = 123;
        return p;             // 堆内存地址，可以，主线程用完后 free
    */
    return NULL;
}

int main(int argc, char **argv)
{
    pthread_t tid;
    int ret;

    sem_init(&g_sem, 0, 0);

    // create thread
    ret = pthread_create(&tid, NULL, my_thread_func, NULL);
    
    if(ret)
    {
        printf("pthread_creat err!\n");
        return -1;
    }

    while(1)
    {
        fgets(g_buf, 1000, stdin);
        sem_post(&g_sem);
    }

    return 0;
}
