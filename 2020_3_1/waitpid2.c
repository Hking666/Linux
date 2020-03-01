#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>


int main()
{

    pid_t pid;
    pid =fork();

    if(pid < 0)
    {
        perror("fork error!");
        exit(1);
    }
    else if(pid == 0)
    {
        printf("this is test for wait\n");
        sleep(2);
        exit(257);
    }
    else
    {
        int status;
        pid_t ret = waitpid(pid,&status,0);
        printf("this is test for wait\n");
        
        if(WIFEXITED(status) && ret == pid)
        {
            printf("wait child 5s success,child reutrn code is : %d.\n",WEXITSTATUS(status));
        }
        else
        {
            printf("wait child faild,return.\n");
            return 1;
        }

    }
    return 0;
}
