#pragma once

#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <queue>
using namespace std;

typedef int(*cal_t)(int,int); // 函数指针类型



class Task{

    private:
       // int number;// 任务编号
        int _x;
        int _y;
        cal_t _handlerTask;//函数指针变量
        int ret; // 任务处理结果
    public:
        Task(int x,int y, cal_t handlerTask )
            :_x(x)
             ,_y(y)
             ,_handlerTask(handlerTask)
             ,is_stop(false)
    {
        
    }

        void RunTask() // 任务处理
        {
            ret =  _handlerTask(_x,_y);
        }

        void ShowRet()
        {
            
            cout<<"thread:"<<pthread_self()<<"Hanlder Task done.  "<<"Result is: "<<ret<<endl;  // 测试
        }

        ~Task()
        {

        }
};

class ThreadPool
{
    public:
        ThreadPool(int num)
            :pthread_num(num)
             
        {

        }

        void InitThreadPool()
        {
            pthread_mutex_init(&lock,NULL);//
            pthread_cond_init(&cond,NULL);
            int i = 0;
            for(; i<pthread_num ; i++)
            {

                pthread_t tid;
                // thread_rountine 函数由static修饰保证参数唯一，不含this 指针
                //  (void*) this  将 this指针作为唯一参数传入， 即将线程池对象传入
                //  此时，创建对象，以及所需使用的成员函数都必须被 public 修饰
                pthread_create(&tid,NULL,thread_rountine,(void*) this);
            }

        }
        ~ThreadPool()
        {
            pthread_mutex_destroy(&lock);
            pthread_cond_destroy(&cond);
        }
    
    public: // this 指针传入thread_rountine // public修饰,供外界访问
        void LockQueue()//给任务队列上锁
        {
                pthread_mutex_lock(&lock);
        }

        void UnlockQueue() // 给任务队列解锁
        {
            pthread_mutex_unlock(&lock);

        }

        bool IsEmpty()
        {
            return t_queue.size() == 0 ? true : false;
        }

        void IdleThread()  // 线程挂起 -- 任务处理完毕
        {
            // 此事还没有 释放锁
            if(is_stop) // 判断是否需要退出  为真
            {
                UnlockQueue(); // 
                pthread_exit((void*)0) // 线程退出
                pthread_num --;// 线程数--
                cout<<"pthread"<<pthread_self()<<"quit!"<<endl // 测试
                return ;
            }
            // 线程挂起 ： 释放锁锁，线程等待
            pthread_cond_wait(&cond,&lock);
        }

        void AddTask(Task &t) // 向线程池中不断添加任务 ---- 相当于生产者  ---- 需要互斥
        {
            //1、 锁住队列
            LockQueue();

            if(is_stop) // 若线程池需要终止，任务就不需要在添加， 
            {
                UnlockQueue(); // 不添加新任务
                return;
            }
            //2、 可存放任务
            //
            t_queue.push(t);
                
            // 3、 通知线程
            NotifyOneThread();
            //4、解锁
            UnlockQueue();

        }

    
        Task GetTask()
        {
            Task t = t_queue.front();
            t_queue.pop();
            return t;
        }

        void Stop() // 终止线程 ， 让整个线程池的所有线程退出
        {
            // 先锁住队列
            LockQueue();
            is_stop = true; // 此时， 所有线程都会判断，然后退出
            UnlockQueue();

            while(pthread_num > 0) // 当前线程数>0
            {
                NotifyAllThreads();
            }
        }
    private:

        void NotifyOneThread() // 通知线程有任务，唤醒线程
        {
            pthread_cond_signal(&cond); // 唤醒一个线程


        }
        
        
        void NotifyAllThreads() // 通知线程没任务，判断线程池需要终止，唤醒所有线程
        {
            pthread_cond_broadcast(&cond); // 唤醒所有线程


        }
        
        
        //在类中，被线程调用的函数，被线程执行，该函数必须是一个静态函数
        ////类成员函数第一个参数时this指针，若不使用 static ,该函数将含义两个参数，
        //而 线程的调用函数 只有一个参数 void* arg 
        // 因此 ， 此时是不合法的
        
        static void *thread_routine(void *arg)  // 线程获取任务 ---- 相当于消费者 ---- 互斥 
        {
                pthread_detach(pthread_self()); //对当前线程进行分离，自己释放资源
                ThreadPool *tp = (ThreadPool*)arg; // 传入当前对象
                for(;;)
                {
                  // 1、 线程访问任务队列前，必须先上锁，防止其他线程访问（互斥），防止新任务进入队列(互斥、同步)
                    tp->LockQueue();
                  // 2、判断当前线程池任务队列是否为空
                    while(tp->IsEmpty()) //任务队列为空   挂起线程 用while
                    {
                        tp->IdleThread(); // (1) 若任务队列为空，线程挂起
                      //  tp->Signal()// (2)唤醒 任务，生产任务
                    }
                    // 任务队列不空
                    
                // 3、有任务，拿出任务
                Task t = tp->GetTask();
                
                tp->UnlockQueue(); // 任务已经被拿出， 此时可以先释放锁，在去处理任务

                // 4、 对任务进行处理
                t.RunTask();
                t.ShowRet();

                }
        }
    private:

        int pthread_num;//线程总数
        std::queue<Task> t_queue; // 任务队列，挂起的任务 ---- 能被所有线程都能从任务队列里面拿任务 ---- 临界资源
        int idles;//线程池中，闲置的线程数量     线程闲置时，idles++ , 线程醒来时， idles-- 
        pthread_mutex_t lock; // 互斥量 --保证任务队列每次只能被执行一种操作
        pthread_cond_t cond; // 定义条件变量  ---- 当队列为空时，线程等待
        bool is_stop;

};
