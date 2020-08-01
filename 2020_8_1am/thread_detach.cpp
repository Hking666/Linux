#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
void* thread1(void* arg)
{
    pthread_detach(pthread_self());
    printf("%s\n",(char*)arg);
    int *p = (int*)malloc(sizeof(int));
    pthread_exit((void*)p);
}


int main()
{

    pthread_t tid;

    pthread_create(&tid,nullptr,thread1,(void*)"thread1 run..");
    
    sleep(2);
    return 0;
}
