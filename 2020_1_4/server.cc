//先实现udp版本的服务器
//
//
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main()
{
    // 1、创建sock
    // AF_INET 是一个 宏， 便是IPV4协议
    // SOCK_DGRAM  表示使用UDP协议
    int sock = socket(AF_INET,SOCK_DGRAM,0);
    if(sock<0)
    {
        perror("socket");
    }

    // 2. 把当前的socket绑定上ip+端口号
    //
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;//
    serv_addr.sin_addr.s_addr = inet_addr("0.0.0.0");
    serv_addr.sin_port = htons(9090);// 大于3000 小于 65535 
    
    int ret =bind(sock,(sockaddr*)&serv_addr,sizeof(serv_addr));
    if(ret < 0)
    {
        perror("bind");
        return 1;
    }
    printf("server start ok!\n");
    
    // 3.处理服务器收到的请求
    while(true)
    {
        // a) 读取客户端请求
        //      面向数据报的函数接口
        char buf[1024] ={0};
        sockaddr_in peer; // 输出参数
        socklen_t len;// 输入输出参数
        ssize_t n = recvfrom(sock,buf,sizeof(buf)-1,0,(sockaddr*)&peer,&len);
        
        if(n<0)
        {
            perror("recvfrom");
            return 1;
            continue;//考虑容错，不能因为一次请求失利就结束整个程序
        }
        buf[n] = '\n';

        // b) 根据请求计算响应
        // [略]  此处写的是一个回显服务器（echo server）
        
        // c) 把响应写回客户端
        n = sendto(sock,buf,strlen(buf),0,(sockaddr*)&peer,len);
        if(n<0)
        {
            perror("sendto");
            continue;
        }
        printf("[%s:%d] buf:%s\n",inet_ntoa(peer.sin_addr),ntohs(peer.sin_port),buf);

    }
    close(sock);
    return 0;
}
