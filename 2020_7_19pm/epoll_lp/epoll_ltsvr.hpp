#pragma once

#include "tcpsvr.hpp"

#include <iostream>
#include <stdio.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <vector>
class EpollSvr
{
    public:
        EpollSvr()
        {
            epoll_fd_ = -1;
        }

        bool InitSvr()
        {

            epoll_fd_ = epoll_create(10);
            if(epoll_fd_<0)
            {
                return false;    
            }
            return true;
        }
        bool AddFd(int fd)
        {
           // 1、组织事件结构
            struct epoll_event ev;
            ev.events = EPOLLIN; // 关心可读事件
            ev.data.fd = fd; 
             
           // 2、调用epoll_ctl 
          //       1、传入操作句柄  2、告诉想干的事情（添加）3、那个文件描述符 4、事件结构
            int ret = epoll_ctl(epoll_fd_,EPOLL_CTL_ADD,fd,&ev);
            if(ret<0)
            {
                perror("epoll_ctl");
                return false;
            
            }
            
            return false;
        }

        bool DeleteFd(int fd)
        {
            int ret  = epoll_ctl(epoll_fd_,EPOLL_CTL_DEL,fd,NULL); // 删除，不需要添加事件结构
            if(ret<0)
            {
                perror("epoll_ctl");
                return false;
            }

            return true;
        }

        bool EpollWait(std::vector<TcpSvr>* out) // 出参
        {

            struct epoll_event   fd_arr[10];

            int ret = epoll_wait(epoll_fd_,fd_arr, sizeof(fd_arr)/sizeof(fd_arr[0]),-1); // -1 阻塞监控 

            if(ret<0)
            {
                perror("epoll_wait");
                return false;
            }
            else if(ret==0)
            {
                printf("timeout");
            }
            if(ret>sizeof(fd_arr)/sizeof(fd_arr[0])); // 防止ret>数组元素个数，从而越界
            for(int i = 0 ; i<ret ;i++)
            {
                TcpSvr ts;
                ts.SetFd(fd_arr[i].data.fd);
                out->push_back(ts);
            }
            return true;
        }
        ~EpollSvr()
        {

        }
    private:
        int epoll_fd_; // epoll 操作句柄
};


