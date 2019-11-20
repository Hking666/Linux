#include <stdio.h>
#include <unistd.h>


int gval =100;
int main()
{
    printf("------hello-----pid:%d\n",getpid());
    pid_t pid = fork();
    if(pid < 0)
    {
        printf("fork error\n");
        return -1;
    }
    if(pid ==0 )
    {
        // 子进程单独运行此代码，因为父进程返回的时子进程pid>0
       gval = 20;
        printf("------child-----pid:%d val:%d\n",getpid(),gval);
    }
    else
    {
        //父进程 -- 进入
        sleep(1);
        printf("------father-----pid:%d val:%d\n",getpid(),gval);
    }
    printf("------world-----pid:%d\n",getpid());

    return 0;
}
