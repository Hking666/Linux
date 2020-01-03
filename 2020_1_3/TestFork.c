#include <stdio.h>
#include <unistd.h>


int main()
{

    pid_t pid = fork();
    printf("getpid:%d pid:%d\n",getpid(),pid);
    sleep(1);
    return 0;
}

