#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{

    
    pid_t pid1 = fork();
    if(pid1==0)
    {
        sleep(5);
        int* p =NULL;
        *p=10;
        
        exit(-1);
    }
    else if(pid1>0)
    {
       int status;
       //waitpid(-1,&status,0);
       // waitpid(1,&status,0);
        int count =0;
      while(0== waitpid(pid1,&status,WNOHANG))
      {
            count++;
      }

      if((status&0x7f )==0)
      {
          printf("正常退出:%d\n",status);
      }
      else
      {
          printf("不正常:%d\n",status);
      }
    }
    return 0;
}
