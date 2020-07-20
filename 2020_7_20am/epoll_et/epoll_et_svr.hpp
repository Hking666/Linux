#pragma once

#include <iostream>
#include "tcpsvr.hpp"
#include <stdio.h>
#include <fcntl.h>
#include <vector>
#include <sys/epoll.h>
#include <stdlib.h>
class EpollSvr
{

    public:
        EpollSvr()
        {
            epoll_fd_ = -1;
        }

        bool Init(size_t size = 10)
        {
            epoll_fd_ = epoll_create(size);
            if(epoll_fd_<0)
                return false;
            return true;
        }

        // 对于ET模式，判断是否需要开启ET模式
        bool AddFd(int fd, bool isEt=true)
        {
            struct epoll_event ev;
            ev.events = EPOLLIN; // 水平模式
            if(isEt)
                ev.events = EPOLLIN|EPOLLET; // ET模式
            ev.data.fd = fd;
            int ret = epoll_ctl(epoll_fd_,EPOLL_CTL_ADD, fd,&ev);
            if(ret<0)
            {
                perror("opoll_ctl");
                return false;
            }

            return true;

        }

        bool DeleteFd(int fd)
        {
            int ret = epoll_ctl(epoll_fd_,EPOLL_CTL_DEL,fd,NULL); 
            if(ret<0)
            {
                perror("epoll_ctl");
                return false;
            }
            return true;
        }

        bool Epoll_Wait(std::vector<TcpSvr>* out)
        {
            // 出参
            struct epoll_event fd_arr[10]; // 将epoll_fd_句柄所指的数组中 的就绪事件 ，保存在 fd_arr数组中

            int ret = epoll_wait(epoll_fd_,fd_arr,sizeof(fd_arr)/sizeof(fd_arr[0]),-1);  // 阻塞i
            if(ret<0)
            {
                perror("epoll_wait");
                return  false;
            }
            else if(ret == 0)
            {
                printf("timeout!!!");
                // continue;
            }

            for(int i = 0 ;i<ret;i++)
            {
                TcpSvr ts;
                ts.setFd(fd_arr[i].data.fd);
                out->push_back(ts);
            }

            return true;
        }
    private:
        int epoll_fd_;

};


