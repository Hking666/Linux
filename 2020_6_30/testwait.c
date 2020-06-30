#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
int main()
{

    int status;
    pid_t pid = fork();
    if(pid<0)
    {
        perror("forkerr");
    }
    else if(0==pid)
    {
        printf("chil1 = %d\n ",getpid());
        //int* p = NULL;
        //*p =10;
        exit(2);
    }
    else
    {
        pid_t pid2 = fork();
        if(0==pid2)
        {
        
            printf("chil2 = %d\n",getpid());
           sleep(100);
            exit(-3);
        }
        int pid3  =  wait(&status);
        printf("  %d %d\n",status,pid3);
    }
    return 0;
}
