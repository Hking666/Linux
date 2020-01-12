#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>

using namespace std;

void show(sigset_t *const &pending)
{
    int i = 1;
    for(;i<=31;i++)
    {
        if(sigismember(pending,i)) // 如果信号集中包含该信号，
        {
            std::cout<<"1 ";
        }
        else
        {
            std::cout<<"0 ";
        }
    
    }

    std::cout<<std::endl;
}
int main()
{

    sigset_t set;
    sigset_t oset;
    sigset_t pending;//pending信号集
    sigemptyset(&set);
    sigemptyset(&oset);
    sigemptyset(&pending);
    
    sigaddset(&set,2);
    sigprocmask(SIG_SETMASK,&set,&oset);
    while(1)
    {
        sigpending(&pending);
        show(&pending);
        sleep(1);
    }
    return 0;
}


