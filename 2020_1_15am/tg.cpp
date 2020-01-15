#include <iostream>
#include <unistd.h>
using namespace std;


int main()
{


    cout<<"job begin"<<endl;
    pid_t id = fork();
    if(id == 0)
    {
        // child
        while(1)
        {
            cout<<"child"<<endl;
            sleep(1);
        }
    }
    else if(id>0)
    {
        // parent
        while(1)
        {
            cout<<"parent"<<endl;
            sleep(1);
        }

    }
    return 0;
}
