#include <iostream>
using namespace std;
#include <signal.h>
#include <functional>
#include <unistd.h>
#include <stdio.h>
//typedef void (myhandler_t)(int);

//typedef std::function<void(int)> myhandler_t;
void MyHandler(int signo)
{
    printf("signo = %d\n",signo);
}
int main()
{
    // signal 替换了信号的原有的处理方式（就会通过
    // signal 的返回值来返回）
    signal(2,MyHandler);    
    signal(3,MyHandler);   
    for(int i = 1 ; i <= 64 ; i++)
    {

        signal(i,MyHandler);
    }
    while(1)
    {
        sleep(1);
    }
    return 0;
}
