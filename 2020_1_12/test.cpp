#include <iostream>
#include <unistd.h>
#include <signal.h>
using namespace std;

void handler(int signo)
{
    cout<<"catch a sig: "<<signo<<endl;
}
int main()
{
    struct sigaction act,oact;
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);

    sigaction(2,&act,&oact);
    while(1)
    {
        cout<<"hello world"<<endl;
        sleep(1);
    }
    return 0;
}
