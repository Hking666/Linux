#include <stdio.h>
#include <unistd.h>
#include <signal.h>



int main()
{

    sigset_t set,oldset;
    sigfillset(&set);
    sigprocmask(SIG_BLOCK,&set,&oldset);//将set添加到阻塞集合
    printf("press enter to continue:\n");
    getchar();
    sigprocmask(SIG_UNBLOCK,&set,NULL);//移除信号集合的信号
    //sigprocmask(SIG_SETMASK,&oldset,NULL);//用保存的原有的替换阻塞集合

    return 0;
}

