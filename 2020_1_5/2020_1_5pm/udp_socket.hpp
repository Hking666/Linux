#pragma once
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
class UdpSocket
{
    public:
        
        UdpSocket()
            :fd_(-1)
        {

        }


        bool CreateSocket()
        {
            fd_ = socket(AF_INET,SOCK_DGRAM,0);
            if(fd_<0)
            {
                perror("socket"); 
                return false;
            }
            return true;
        }

        bool Bind(const std::string& ip , uint16_t port)
        {
            struct sockaddr_in addr;
            addr.sin_family = AF_INET;
            addr.sin_port = htons(port);
            addr.sin_addr.s_addr = inet_addr(ip.c_str());

            int ret = bind(fd_,(sockaddr*)&addr,sizeof(addr));
            if(ret< 0)
            {
                perror("bind");
                return false;
            }
            return true;
        }

        bool Close()
        {
           close(fd_);
           return fd_;
        }
        // 出了成功失败，还需要返回什么？
        // 1. 从网卡上读缓存区读到的数据
        //              string*  buf    或 string& buf
        // 2、对方的ip、port // 输出参数 
        //              NULL  代表不关注对方Ip 或 端口
        //
        bool RecvFrom(std::string* buf,std::string* ip=NULL , uint16_t* port= NULL)
        {
            char temp[BUFSIZ] = {0};
            sockaddr_in peer;
            socklen_t  len = sizeof(peer);
                            
            ssize_t read_size = recvfrom(fd_,temp,sizeof(temp)-1,0,(sockaddr*)&peer,&len);
            
            if(read_size<0)
            {
                perror("recvfrom");
                return false;
            }
            
            //将读到的缓冲区内容放到输出参数中
            // 也可以  *buf = temp   将 temp 字符数组 赋值给 string
            buf->assign(temp,read_size);

            // 
            if(ip != NULL)
            {
                *ip = inet_ntoa(peer.sin_port);// 将数字ip地址转换成点分十进制，得到的字符串再 赋值给 string* ip
            }

            if(port != NULL)
            {
                *port = ntohs(peer.sin_port); // 将网络序转换成主机序 赋值 给 port
            }

            return true;
        }
        // 1. 发送什么字符串？
        // 2. 发送给谁？目的ip地址和端口号
        bool SendTo(const std::string& msg ,const std::string& ip, uint16_t port)
        {
                sockaddr_in addr;
                addr.sin_family = AF_INET;
                addr.sin_addr.s_addr = inet_addr(ip.c_str());
                addr.sin_port = htons(port);

                ssize_t write_size = sendto(fd_,msg.c_str(),msg.size(),0,(sockaddr *)&addr ,sizeof(addr));
                
                if(write_size < 0)
                {
                    perror("sendto");
                        return false;
                }
                return true;
        }
    private:
        int fd_;
};

