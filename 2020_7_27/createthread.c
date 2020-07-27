#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

typedef struct thread_info
{
    int thread_num_;
    thread_info()
    {
        thread_num_ = -1;
    }
}THREADINFO;

void* thread_start(void* arg)
{
    THREADINFO* ti = (THREADINFO*)arg;
    while(1)
    {
        printf("i am new thread~~~~: %d\n", ti->thread_num_);
        sleep(1);
    }
    //对于传递进来的对上开辟的内存，可以在线程入口函数结束的时候，释放掉，不会导致程序有内存泄漏的风险
    delete ti;
    return NULL;
}

int main()
{
    pthread_t tid;
    int ret;
    int i = 0;
    for(; i < 4; i++)
    {
        THREADINFO* threadinfo = new thread_info();
        //堆上开辟的
        threadinfo->thread_num_ = i;
        ret = pthread_create(&tid, NULL, thread_start, (void*)threadinfo);
        if(ret < 0)
        {
            perror("pthread_create");
            return 0; 
        }
    }

    while(1)
    {
        printf("i am main thread~~~\n");
        sleep(1);
    }
    return 0;
}
