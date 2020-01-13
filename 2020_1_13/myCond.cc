#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <string>

using namespace std;

pthread_mutex_t lock;
pthread_cond_t cond;//定义条件变量

void *r1(void *arg)
{
    string t1 = (char *)arg;
    while(1)
    {
        pthread_cond_wait(&cond,&lock);
        cout<< t1 << " is running" << endl;
    }

}

void *r2()
{
    while(1)
    {
        pthread_cond_signal(&cond);
        sleep(2);
    }

}

int main()
{
    pthread_mutex_init(&lock,NULL);
    pthread_cond_init(&cond,NULL); // 创建条件变量
    pthread_t t1,t2;
    pthread_create(&t1,NULL,r1,(void*)"pthread 1");
    pthread_create(&t2,NULL,r2,(void*)"pthread 2");
    
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);
    return 0;
}
