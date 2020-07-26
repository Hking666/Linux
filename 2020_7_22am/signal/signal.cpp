#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void handler(int sig)
{
    printf("catch a sig :%d\n",sig);
}
int main()
{

    signal(2,handler);
    while(1)
    {
        sleep(1);
    }
    return 0;
}