#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <vector>

using namespace std;

volatile int tickets = 10000;//票的数量
pthread_mutex_t lock;// 互斥锁



void *BuyTicket(void *arg)
{
    int number = (int)arg;
    while(1)
    {
        pthread_mutex_lock(&lock);//每次抢票   加锁
        if(tickets > 0)
        {
            usleep(1000);
            cout<<"thread "<<number<<"get a ticket: "<<tickets<<endl;
            tickets--;
            pthread_mutex_unlock(&lock);//抢票成功 解锁
        }
        else
        {
            pthread_mutex_unlock(&lock);// 避免在跳出时，没有释放锁
            break;
        }
    }
    return (void*)0;
}

struct attr{

    int number;
    pthread_t tid;
};

int main()
{
    int num = 10;
    
   // pthread_create(&id , NULL ,thread_run,(void*)"thread 1");
    vector<attr> thread_list(num);

    pthread_mutex_init(&lock,NULL);


    int i =  0;
    for(;i<thread_list.size();i++)
    {
        pthread_create(&(thread_list[i].tid),NULL,BuyTicket,(void*)i);
        thread_list[i].number = i;
    }

    for(i = 0 ; i < thread_list.size();i++ )
    {
        pthread_join(thread_list[i].tid,NULL);
    }
    pthread_mutex_destroy(&lock);
    return 0;
}
