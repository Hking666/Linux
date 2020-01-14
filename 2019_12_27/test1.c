#include <stdio.h>
#include <signal.h>
#include <unistd.h>
int a =1;
void sigcb(int signo)
{
   // printf("signo=[]\n");    
   printf("signo=[%d]\n",signo);    
}

int main(int argc ,char *argv[])
{
    while(a)
    {
        printf("%d\n",a);
        sleep(1);
        signal(SIGINT,sigcb);
        signal(SIGQUIT,sigcb);
    }
    return 0;
}
