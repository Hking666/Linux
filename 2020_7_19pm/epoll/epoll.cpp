#include <stdio.h>
#include <unistd.h>
#include <sys/epoll.h>

int main()
{
    int epollfd = epoll_create(10);
    if(epollfd<0)
    {
        perror("epoll");
        return -1;
    }
    struct epoll_event ev;
    ev.events =EPOLLIN;
    ev.data.fd =0;
    epoll_ctl(epollfd,EPOLL_CTL_ADD,0,&ev);

    while(1)
    {
        struct epoll_event fd_arr[10];
        int ret =epoll_wait(epollfd,fd_arr,sizeof(fd_arr)/sizeof(fd_arr[0]),3000);
        if(ret<0)
        {
            perror("epoll_wait");
            return 0;
        }
        else if()
    }


    return 0;
}
