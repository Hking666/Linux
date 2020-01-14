#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;
pthread_rwlock_t rwlock;

int book = 0;
void *Reader(void *arg)
{
    for(;;)
    {
        pthread_rwlock_rdlock(&rwlock); // 读加锁

        cout<<"read book"<<book<<endl;

        pthread_rwlock_unlock(&rwlock);
        usleep(300000);
    }
}

void *Writer(void *arg)
{
    for(;;)
    {
        pthread_rwlock_rdlock(&rwlock); // 写加锁

        book++;
        pthread_rwlock_unlock(&rwlock);
        cout<<"write book: "<<book<<endl;

        sleep(1);
    }
}
int main()
{

    pthread_rwlock_init(&rwlock,NULL);

    pthread_t r,w;
    pthread_create(&r,NULL,Reader,(void *)NULL);
    pthread_create(&w,NULL,Writer,(void *)NULL);

    pthread_join(r,NULL);
    pthread_join(w,NULL);
    pthread_rwlock_destroy(&rwlock);
    

}
