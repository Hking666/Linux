#include <stdio.h>
#include <unistd.h>
#include <pthread.h>


int  count =0;
void* ThreadEntry(void* thr)
{
    while(1)
    {
        printf("I am thread:%s\n",(char*)thr);
        printf("ThreadEntryc--->count:%d\n",count++);
       // printf("ThreadEntryc--->count:%d\n",countstack++);
        sleep(1);
    }
    return NULL;
}

int main()
{
    int countstack =0;

    pthread_t tid;
    
    char *str ="hello nihaoa1";
    pthread_create(&tid,NULL,ThreadEntry,str);

    
        sleep(1);
        printf("I am main thread\n");
      while(1)
      {
          sleep(1);
        printf("Main--->count::%d\n",count);
        printf("Main--->countstack::%d\n",countstack);
      }
        // pthread_cancel(tid);
      pthread_join(tid,NULL); 
      //printf("new thread 已经被回收了\n");
      
    return 0;
}

