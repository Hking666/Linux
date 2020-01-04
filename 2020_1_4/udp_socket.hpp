#pragma once
#include <stdio.h>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
class UdpSocket
{
public:

    UdpSocket()
        :fd_(-1)
    {

    }

    // 打开一个 udp 的socket
    // 返回 true 表示创建成功，false 失败
    bool Socket() // 创建socket
    {
        fd_ = socket(AF_INET,SOCK_DGRAM,0);
        if(fd_<0)
        {
            perror("socket");
            return false;
        }
        return true;
    }
    
    bool Close()
    {
        if(fd_ != -1)
            close(fd_);

        return true;
    }

    bool Bind(const std::string& ip,uint16_t port)
    {
        //根据参数构造一个 sockaddr_in 结构
        //调用 bind
        sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = inet_addr(ip.c_str());
        addr.sin_port = htons(port);
        int ret = bind(fd_,(sockaddr*)&addr,sizeof(addr));
        if(ret<0)
        {
            perror("bind");
            return false;
        }
        return true;
    }

    // 1.读到的数据
    // 2.对方的 IP 地址
    // 3.对方的端口号
    bool RecvFrom(std::string* temp,std::string* ip = NULL  , uint16_t *port = NULL)
    {
        char temp[1024*10] = {0};
        sockaddr_in peer;
        socklen_t len =sizeof(peer);
        ssize_t read_size =recvfrom(fd_,temp,sizeof(temp)-1,0,(sockaddr*)&peer,&len);
        if(read_size < 0)
        {
            perror("recvfrom");
            return false;
        }

        buf
        return true;
    }

    bool SendTo()
    {

    }

private:
    int fd_;
};
