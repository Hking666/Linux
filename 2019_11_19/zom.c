#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{

    int pid = fork();
    if(pid <0)
    {
        return -1;
    }
    else if(pid == 0)
    {
        // 子进程
        sleep(5);
        exit(0);
    }
    else
    while(1)
    {
        sleep(1);
    }
    return 0;
}
