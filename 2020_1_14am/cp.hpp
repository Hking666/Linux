#pragma once

#include <iostream>
#include <queue>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <vector>
#include <semaphore.h>
class RingQueue
{
    public:
        RingQueue(int cap)
            :_cap(cap)
            ,ring(cap)// 指定vector数组元素个数
        {
            c_step = p_step = 0; // 生产者与消费者在同一位置
            sem_init(&blank_sem,0,_cap);//生产者格子资源初始值为环形格子数
            sem_init(&data_sem,0,0);// 消费者数据资源初始值为0；生产者没有生产
        }
        
        ~RingQueue()
        {
            sem_destroy(&blank_sem);
            sem_destroy(&data_sem);
        }


        void PushData(const  int &data)
        {
            P(blank_sem); //申请格子资源,格子信号量减1
            ring[p_step] = data;//在申请格子上放数据,此时数据就变多了
            V(data_sem);// 数据信号量加1
            p_step++;
            p_step %= _cap;

        }

        void PopData(int &data)// 消费者消费
        {
            P(data_sem);// 申请数据资源，数据信号量减1
            data = ring[c_step]; //有数据了，数据跟随消费者的脚步
            V(blank_sem); // 数据被拿走了 ， 此时格子就多出来了
            c_step++;
            c_step %= _cap;
  
    private:
        
            void P()
            {
                sem_wait(&sem);
            }

            void V()
            {
                sem_post(&sem);
            }
    private:
        std::vector<int> ring;// 环形队列
        int _cap;//容量
        sem_t blank_sem;// 生产者格子资源；
        sem_t data_sem;//  消费者数据资源
        
        int c_step;//消费者脚步
        int p_step;//生产者脚步

        
};
