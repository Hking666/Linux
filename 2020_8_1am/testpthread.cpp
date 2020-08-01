#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <string>
#include <string.h>
void* thread1(void *arg)
{
    std::cout<<(char*)arg<<std::endl;
    std::cout<<"nihao"<<std::endl;
    pthread_cancel(pthread_self());
    
}
int main()
{
    pthread_t tid;
    void* value;
    int ret  = pthread_create(&tid,nullptr,thread1,(void*)"Linnux");
    pthread_join(tid,&value);
    printf("ret = %d\n",*(int*)value);
    if(ret != 0)
    {
       fprintf(stderr,"pthread_creat:%s\n",strerror(ret));
        exit(EXIT_FAILURE);
    }

    while(1)
    {
        sleep(1);
    }
    return 0;
}

