#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>


int main()
{
    pid_t pid;

    if((pid=fork()) < 0)
    {
        perror("fork"),exit(1);
    }
    
    if(pid == 0)
    {
        sleep(10);
        exit(10);
    }
    else 
    {
        int status;
        int ret = wait(&status);

        if(ret > 0 && (ret & 0x7F) == 0)
        {
            printf("child exit code:%d\n",(status>>8)&0XFF);
        }
        else if(ret > 0) 
        {
            printf("sig code: %d\n",status&0x7F);
        }
        
    }
    
}
