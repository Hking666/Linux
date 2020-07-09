#pragma once

#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string>
#include <stdlib.h>

class TcpSvr
{
    public:

        TcpSvr()
        {
            sockfd = -1;
        }
        // 创建套接字
        bool CreatSocket()
        {
            sockfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

            if(sockfd<0)
            {
                perror("socket");
                return false;
            }
            return true;
        }
        // 绑定地址信息

        bool Bind(std::string& ip,uint16_t port)
        {
            struct sockaddr_in  addr;
            addr.sin_family = AF_INET;
            addr.sin_port = htons(port);
            addr.sin_addr.s_addr = inet_addr(ip.c_str());

            int ret  = bind(sockfd,(struct sockaddr*)&addr,sizeof(addr));

            if(ret < 0)
            {
                perror("bind");
                return false;
            }

            return true;
        }
        // 侦听 

        bool Listen(int backlog = 5)
        {
            int ret  = listen(sockfd,backlog);
            if(ret < 0)
            {
                perror("listen");
                return false;
            }

            return true;
        }
        // 获取链接
        //bool Accept(struct sockaddr_in* peeraddr , int* sockfd)//都是输出型参数 sockfd 输出型参数
        bool Accept(struct sockaddr_in* peeraddr , TcpSvr* tcp)//都是输出型参数 sockfd 输出型参数
        {
           socklen_t  addrlen = sizeof(struct sockaddr_in);
           int svrfd = accept(sockfd,(struct sockaddr*)peeraddr,&addrlen);

           if(svrfd<0)
           {
               perror("accept");
               return false;
           }

          //*sockfd = svrfd;
          tcp->sockfd = svrfd;
           return true;
        }
        
        // 发起链接(client)
        bool Connect(std::string& ip,uint16_t port)
        {
            struct sockaddr_in destAddr;
            destAddr.sin_family = AF_INET;
            destAddr.sin_port = htons(port);
            destAddr.sin_addr.s_addr = inet_addr(ip.c_str());

            int ret  = connect(sockfd,(struct sockaddr*)& destAddr,sizeof(destAddr));
            if(ret<0)
            {
                perror("connect");
                return false;
            }

            return true;
        }
        //接收信息
        bool Recv(std::string* data )
        {
            char buff[1024] ={0};
            int recvSize = recv(sockfd,buff,sizeof(buff)-1,0);
            if(recvSize<0)
            {
                perror("recv");
                return false;
            }
            else if(recvSize==0)
            {
                printf("peer shutdown connect!!!");

                return false;
            }
            (*data).assign(buff,recvSize); // 将接收的数据返回给调用者；
            return true;
        }
        // 发送信息
        bool Send(std::string& data)
        {
            int sendSize = send(sockfd,data.c_str(),data.size(),0);
            if(sendSize<0)
            {
                perror("send");
                return false;
            }
            return true;
        }

        // 关闭连接
        void Close()
        {
            close(sockfd);
            sockfd = -1;
        }
    private:
        int sockfd;
};


