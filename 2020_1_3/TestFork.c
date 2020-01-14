#include <stdio.h>
#include <unistd.h>


int main()
{

    pid_t pid = fork();
    printf("getpid:%d pid:%d\n",getpid(),pid);
    if(0==pid)
    {
        printf("I am child:[getpid:%d] [pid:%d]\n",getpid(),pid);
    }
    else if(pid>0)
    {
        printf("I am father:[getpid:%d] [pid:%d]\n",getpid(),pid);
    }
    else
    {
        perror("fork:");
    }
    sleep(1);
    return 0;
}

