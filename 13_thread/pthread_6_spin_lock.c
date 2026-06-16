#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <string.h>

/*
而 mutex 拿不到锁时，可能发生：

线程 A 拿不到 mutex
    ↓
进入内核
    ↓
把线程 A 挂起/睡眠
    ↓
CPU 切换去运行别的线程
    ↓
线程 B unlock
    ↓
内核唤醒线程 A
    ↓
线程 A 被调度回来
    ↓
线程 A 继续执行

这里会有额外开销：
用户态/内核态切换
线程状态切换：running -> sleeping -> runnable
调度器参与
上下文切换
CPU cache 可能失效
*/

/*
锁很快释放：
    spinlock 可能更快，因为它不用睡眠/唤醒

锁要等比较久：
    mutex 更好，因为等待线程睡眠，不浪费 CPU
*/

pthread_spinlock_t spinlock;
int shared_data = 0;

static void *my_thread_func (void *data)
{
	int i = (int)(intptr_t)data;
	while (1)
	{
		pthread_spin_lock(&spinlock);
		shared_data++;
		printf("Thread %d is modifying the shared data: %d\n", i, shared_data);
		pthread_spin_unlock(&spinlock);
		sleep(1);		
	}

	return NULL;
}


int main(int argc, char **argv)
{
	pthread_t tid;
	int ret;
	int i;
	
	pthread_spin_init(&spinlock, PTHREAD_PROCESS_PRIVATE);
	
	/* 创建线程 */
	for (i =0; i < 10; i++)
	{
		ret = pthread_create(&tid, NULL, my_thread_func, (void *)(intptr_t)i); 
		// PS: 使用(void *)i, 这非常的不好，非常非常的不好
		// 这种写法相当于把 i 的数值拷贝进了线程参数里。 最好还是直接传指针
		if (ret)
		{
			printf("pthread_create err!\n");
			return -1;
		}
	}


	while (1)
	{
		sleep(100);
	}
	
	pthread_spin_destroy(&spinlock);
	return 0;
}
