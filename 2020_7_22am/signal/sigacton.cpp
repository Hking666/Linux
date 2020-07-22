#include <stdio.h>
#include <signal.h>
#include <unistd.h>
void sighandl(int signo)
{
    printf("catch a sig:%d\n",signo);
}

int main()
{
    struct sigaction newact;
    newact.sa_handler = sighandl;
    sigemptyset(&newact.sa_mask);
    newact.sa_flags = 0;

    struct sigaction oldact;
    sigaction(2,&newact,&oldact);

    while(1)
    {
        sleep(1);
    }
    return 0;
}



