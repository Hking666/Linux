#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{

    pid_t pid;
    if((pid = fork()) < 0)
    {
        perror("fork error");
        exit(1);
    }

    if(pid == 0)
    {
        sleep(30);
        exit(2);
    }
    else
    {
        int status;
        pid_t ret = waitpid(-1,&status,0);
        
        if(ret > 0 && (status & 0x7F)==0)//该进程有子进程退出 且 正常退出
        {
            printf("child exit code: %d\n",(status>>8)&0xFF); //获取前八位的退出状态 
             
        }
        else if(ret > 0) // 该进程有子进程退出 ， 非正常退出
        {
            printf("sig code: %d",(status&0x7F));
        }
    }

}

