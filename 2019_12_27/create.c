#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *thr_start(void *arg)
{
    while(1)
    {
        printf("i am normal pthread ---ptr :%s\n",(char*)arg);
        sleep(1);
    }
    return NULL;
}
int main()
{
    pthread_t tid;
    int ret;
    char *ptr ="haha";
    ret =pthread_create(&tid,NULL,thr_start,(void*)ptr);
    if(ret != 0)
    {
        perror("pthread_create error");
        return -1;
    }
    while(1)
    {
        printf("I am mian thread-----\n");
        sleep(1);

    }
    return 0;
}
