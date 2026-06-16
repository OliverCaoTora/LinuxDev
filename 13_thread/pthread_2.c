#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

static char g_buf[1000];

static int g_hasData = 0;

static void *my_thread_func(void *data)
{
    while(1)
    { 
        // sleep(1); 
        while(g_hasData == 0);
        printf("revc: %s\n", g_buf);
        g_hasData = 0;
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
        g_hasData = 1;
    }

    return 0;
}
