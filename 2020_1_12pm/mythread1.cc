#include <iostream>
#include <unistd.h>
#include <pthread.h>


using namespace std;
void *thread_run(void *arg)
{
    const char* thread_name = (const char*)arg;
    
    while(1)
    {
        cout <<thread_name<<" is running..."<<endl;
        sleep(1);
    }

    //return (void*)123;
}

int main()
{
    pthread_t id;
    
    pthread_create(&id,NULL,thread_run,(void*)"thread 1");
    
    pthread_detach(id); 
    
    sleep(1);
    sleep(3);
    
    // 取消线程
   // pthread_cancel(id);
    //void* ret;
    int ret =  pthread_join(id,NULL);
    std::cout<<"ret: "<<ret<<endl;
    return 0;
}
