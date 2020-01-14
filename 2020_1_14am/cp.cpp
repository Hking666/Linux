#include "cp.hpp"

using namespace std;

const int num = 16;

void *consume_routine(void *arg)
{
    int d;
    RingQueue *q = (RingQueue *)arg;
    for(;;)
    {
        q->PopData(d);
        cout<<"consume done,data is :" <<d<<endl;
    }
}

void *product_routine(void *arg)
{
    RingQueue *q = (RingQueue *)arg;
    srand((unsigned long) time(NULL));
    for(;;)
    {
        int d = rand()%100+1;
        q->PushData(d);

        cout<<"product done,data is :" <<d<<endl;
    }
}
int main()
{
    RingQueue *p = new RingQueue(num); //创建队列
    pthread_t c, p;
    pthread_create(&c,NULL,consume_routine,(void*)p);
    pthread_create(&p,NULL,product_routine,(void*)p);

    pthread_join(c,NULL);
    pthread_join(p,NULL);
    delete(p);
    return 0;
}
