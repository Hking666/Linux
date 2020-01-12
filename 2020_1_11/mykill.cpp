#include <iostream>
using namespace std;
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>

void handler(int signo)
{
    cout <<"catch a sig ,signo:"<<signo<<endl;
}

int main(int argc , char *argv[])
{
    kill(atoi(argv[1]),atoi(argv[2])); 
    return 0;
}


