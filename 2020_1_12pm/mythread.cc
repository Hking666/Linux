#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;
void *thread_routine(void *arg)
{
    const char *thread_name = (const char*)arg;
   // while(1)
   // {
   //     cout<<thread_name<<"running..."<<endl;
   //     sleep(5);
   // }
     cout<<thread_name<<"running..."<<endl;
     sleep(4);
     return (void*)123;
}

int main()
{

    pthread_t tid;
    pthread_create(&tid,NULL,thread_routine,(void*)"thread 1");

   // while(1)
   // {
        cout<<"main thread running..."<<endl;
   //     sleep(1);
   // }
        void* ret ;
        pthread_join(tid,&ret);// 主线程等待
        cout<<"new thread quit ,code is: "<<(int)ret<<endl;
}
