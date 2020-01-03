#include <stdio.h>
#include <unistd.h>
int main()
{

    printf("pid:%d\n",getpid());//获取当进程pid
    printf("ppid:%d\n",getppid());//获取父进程pid
    return 0;
}
