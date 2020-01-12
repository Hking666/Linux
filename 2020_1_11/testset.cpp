#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>

using namespace std;

void show(const sigset_t * pending)
{
    for(int i = 1;i<=31;i++)
    {

        if(sigismember(pending,i))
        {
            cout<<"1";
        }
        else
        {
            cout<<"0";
        }
    }
    cout<<endl;
}
int main()
{

    sigset_t set;
    sigset_t oset;
    sigset_t pending;

    sigemptyset(&set);
    sigemptyset(&oset);
    sigemptyset(&pending);

    sigprocmask(SIG_SETMASK,&set,&oset);
    sigaddset(&set,2);
    sigaddset(&set,20);
    sigaddset(&set,3);
    sigprocmask(SIG_SETMASK,&set,&oset);

    sigdelset(&set,3);
    sigprocmask(SIG_SETMASK,&set,&oset);

    while(1)
    {
        sigpending(&pending);
        show(&pending);
        sleep(1);
    }
    return 0;
}
