#include <stdio.h>
#include <unistd.h>
#include <signal.h>
int main()
{

    // int kill(pid_t pid,int sig);
    //    给pid进程发送sig信号
    
    alarm(3);
    while(1)
    {
        alarm(0);// 取消上个alarm(3)
        printf("hello!\n");
        sleep(5);
        kill(getpid(),SIGKILL);//给当前进程发送9号信号
    }
    return 0;
}
