#include <iostream>
using namespace std;
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>


volatile int i = 0;
void handler(int signo)
{
    
    cout<<i<<endl;
    cout <<"catch a sig ,signo:"<<signo<<endl;
    exit(1);
}

int main()
{
    signal(14,handler);

    
    alarm(1);
    while(1)
    {
        i++;
        
    }
    return 0;
}


