#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
int a =0;
int b =0;
int test()
{
    a++;
    sleep(5);
    b++;
    return a+b;
}

void sigcb()
{
    printf("signal---------%d\n",test());
}
int main()
{
    signal(SIGINT,sigcb);
    printf("%d",test());

    return 0;
}
