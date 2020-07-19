#include <stdio.h>
#include <unistd.h>
#include <sys/epoll.h>

int main()
{

    // 1、创建epoll操作句柄
    

    int epoll_fd = epoll_create(10);
    if(epoll_fd<0)
    {
        return -1;
    }
    //2、组织事件结构
    struct epoll_event ev;
    ev.events = EPOLLIN|EPOLLET;  // 边缘触发
    ev.data.fd = 0;
    //3、添加文件描述符
    epoll_ctl(epoll_fd,EPOLL_CTL_ADD,0,&ev);
    //4、监听
    while(1)
    {
        struct epoll_event fd_addr[10];
        int ret = epoll_pwait(epoll_fd,fd_addr,sizeof(fd_addr)/sizeof(fd_addr[0]),-1);
        if(ret<0)
        {
            return -1;
        }

        for(int i=0;i<ret;i++)
        {
            if(fd_arr[i].data.fd==0)
            {}
        }
    }
    return 0;
}
