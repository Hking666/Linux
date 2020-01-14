#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sigcb(int signo)// 信号回调函数 
{
    printf("recv a signal:%d\n",signo);
}
void prin()
{

    printf("nihao");
}
int main()
{
    while(1)
    {
        prin();
        printf("hello\n");
        sleep(1);
       // signal(SIGINT,SIG_IGN);// SIGINT 中断信号,SIG_IGN 信号被忽略
       // signal(SIGINT,sigcb);// SIGINT 中断信号,
       // signal(SIGQUIT,sigcb);// SIGQUIT 退出信号,
        struct sigaction act,old;
        act.sa_handler = sigcb;//设置回调函数
        act.sa_flags = 0;
        sigemptyset(&act.sa_mask) ;//清空信号
        sigaction(SIGINT,&act,&old);
    }
    return 0;
}
