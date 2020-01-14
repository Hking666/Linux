#include "thread_pool.hpp"

#define NUM 5
int add(int x ,int y)
{
    return x+y;
}
int main()
{

    // 构造线程池对象
    ThreadPool *tp = new ThreadPool(NUM);

    // 初始化
    tp->InitThreadPool();

    int count = 1;
    
    while(1)
    {
        sleep(1);
        //构建任务
        Task t(count,count-1,add);
        
        // 添加任务
        tp->AddTask(t);
        count++;
    }
    return 0;
}
