#pragma once

#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
class Sock
{
    private:
        int sock;
        std::string ip;
        int port;

    public:
        Sock(std::string &ip_, int &port_)
            :ip(ip_)
             ,port(port_)
        {

        }

        void Socket()
        {
            
            sock = socket(AF_INET,SOCK_DGRAM,0);//返回套接字描述符
            if(sock < 0)
            {
                std::cerr<<"socket error!"<<std::endl;
                exit(2);
            }
            
        }


        void Bind()
        {
            struct sockaddr_in local_;// 要和本机的 ip地址和端口号（套接字）进行绑定
            local_.sin_family = AF_INET;
            local_.sin_port = htons(port);//
            local_.sin_addr.s_addr = inet_addr(ip.c_str());

            if(bind(sock,(sockaddr*)&local_,sizeof(local_))<0)
            {
                std::cerr<<"bind error!"<<std::endl;
                exit(3);

            }
        }




        void Recv(std::string &str_, struct sockaddr_in &peer , socklen_t &len)
        {
            char buf[1024];// 保证以\0 结尾
            len = sizeof(sockaddr_in);// sockaddr_in 是结构体类型 大小 = sizeof (peer) 
            ssize_t s  = recvfrom(sock,buf,sizeof(buf),0,(struct sockaddr*)&peer,&len);
            // peer 客户端的套接字信息
            if(s>0)
            {
                buf[s] = 0; // 设置\0
                str_ = buf;// 将c语言风格字符串转成c++,保证以\0结尾
                
            }

        }

        void Send(std::string &str_,struct sockaddr_in &peer,socklen_t &len)
        {
            sendto(sock,str_.c_str(),str_.size(),0,(struct sockaddr*)&peer,len);
        }

        ~Sock()
        {
            close(sock);
        }
};



class UdpServer // 服务器
{

    private:
        Sock sock;


    public:
        UdpServer(std::string ip_,int port_)
            :sock(ip_,port_)
        {
            
        }
        
        void InitServer()
        {
            sock.Socket();
            sock.Bind();
        }

        void Start()
        {

            struct sockaddr_in peer;// 客户端套接字
            socklen_t len; // 客户端
            std::string message;
            for(;;)
            {
                sock.Recv(message,peer,len);
                //peer.sin_addr（网络序列）---》 主机序列
                //peer.sin_port (网络序列) --- 》 主机序列27
                std::cout<<"["<<inet_ntoa( peer.sin_addr)<<":"<<ntohs(peer.sin_port)<<"]#clien# "<<message<<std::endl;
                message += "server";
                sock.Send(message,peer,len);
                std::cout<<"server# echo success! "<<message<<std::endl;
            }
        }


        ~UdpServer()
        {
            sock.~Sock();
        }
};










