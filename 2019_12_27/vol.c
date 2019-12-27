#include <stdio.h>
#include <signal.h>
#include <unistd.h>
int a =1;
void sigcb(int signo)
{
   
   printf("signo=[%d]\n",signo);    
}

int main(int argc ,char *argv[])
{
    
       signal(SIGQUIT,sigcb);
       while(a)
       {
          a =2; 
       }
       printf("normal exit!!!\n");
    
    return 0;
}
