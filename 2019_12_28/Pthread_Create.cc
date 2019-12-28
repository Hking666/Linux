#include <iostream>
using namespace std;
#include <pthread.h>
#include <unistd.h>
void* handle(void* arg)
{
    while(1)
    {
        cout<<"I am HanlePthread"<<endl;
        sleep(1);
    }

}
int main()
{
    pthread_t tid;
    pthread_create(&tid,NULL,handle,NULL);
    while(1)
    {
        cout<<"I am Main pthread "<<endl;
        sleep(1);
    }
    return 0;
}
