#pragma once
#include "udp_socket.hpp"
#include <assert.h>
#include <functional>
// 通用服务器类
// 1、读取请求
// 2、根据请求计算响应
// 3、把响应写回到客户端
// 1. 3. 是固定套路， 不管啥场景，代码都一样
// 2 是和业务相关，所以就把 2 对应的代码提前成一个回调函数
//
//
//
//typedef void (*Handle)(const std::string& req , std::string* resp); //函数指针
typedef std::function<void(const std::string&,std::string*)> Handler;

class UdpServer
{
    public:
        UdpServer()
        {
            assert(sock_.CreateSocket()); 
        }

        ~UdpServer()
        {
            sock_.Close();
        }

        bool Start(const std::string & ip , uint16_t port ,Handle handle)
        {

            //1. 创建socket
            //2. 绑定端口号
            bool ret = sock_.Bind(ip ,port);
            if(!ret)
            {
                return false;
            }

            //3.进入死循环
            while(true)
            {
                // 处理每个请求
                // a） 读取请求
                std::string req;
                std::string peer_ip;
                uint16_t peer_port;
                sock_.RecvFrom(&req,&peer_ip,&peer_port);
                
                std::string resp;
                // b)  根据请求计算响应
                handle(req,&resp)//给一个请求，计算生成响应
                // c)把响应返回给客户端
                sock_.SendTo(resp,peer_ip,peer_port);
            }
        }

    private:
        UdpSocket sock_;
};
