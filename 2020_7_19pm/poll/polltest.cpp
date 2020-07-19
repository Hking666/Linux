#include <iostream>
#include <unistd.h>
#include <poll.h>
#include <stdio.h>

int main()
{

    // 1、定义事件结构数组
    struct pollfd fd_arr[10];
    fd_arr[0].fd =0; // 关心0号文件描述符
    fd_arr[0].events = POLLIN; // 关心事件为 可读事件 POLLIN

    //2、监控
    while(1)
    {
        int ret =poll(fd_arr,1,1000); // fd_arr有效元素为1个 ， 监控1000毫秒
        if(ret<0)
        {
           perror("poll\n");
           return -1;
        }
        else if(ret ==0) // 超时
        {
            printf("timeout\n");
        }
        //若有多个有效文件描述符
        for(int i = 0 ; i<ret;i++)
        {
            if(fd_arr[i].events == POLLIN)
            {
                char buf[1024]={0};
                read(fd_arr[i].fd,buf,sizeof(buf)-1);
                printf("read content is =%s\n",buf);
            }
        }
    }

    //2、当产生可读事件的时候处理事件


    return 0;
}
