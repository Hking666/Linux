/*================================================================
*   Copyright (C) 2020 Sangfor Ltd. All rights reserved.
*   
*   文件名称：main.cpp
*   创 建 者：Ann
*   创建日期：2020年05月17日
*   描    述：
*
================================================================*/

#include "tcpsvr.hpp"
#include "epoll_svr.hpp"

#define CHECK_RET(p) if(p != true){return 0;}

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        printf("Start this process use in: ./tcpsvr [ip] [port]\n");
        return 0;
    }

    std::string ip = argv[1];
    uint16_t port = atoi(argv[2]);

    TcpServer listen_tcpsvr;
    CHECK_RET(listen_tcpsvr.CreateSock());
    CHECK_RET(listen_tcpsvr.Bind(ip, port));
    CHECK_RET(listen_tcpsvr.Listen(5));

    EpollSvr es;
    es.AddFd(listen_tcpsvr.GetFd());

    while(1)
    {
        std::vector<TcpServer> output;
        if(!es.EpollWait(&output))
        {
            continue;
        }

        for(size_t i = 0; i < output.size(); i++)
        {
            //1.有新连接到来
            //  需要调用accept函数
            //  将接收回来的套接描述符在添加到epoll当中
            if(output[i].GetFd() == listen_tcpsvr.GetFd())
            {
                TcpServer newts;
                struct sockaddr_in peeraddr;
                listen_tcpsvr.Accept(newts, &peeraddr);
                printf("have a new connection %s : %d\n", inet_ntoa(peeraddr.sin_addr), ntohs(peeraddr.sin_port));

                es.AddFd(newts.GetFd(), true); 
            }
            else
            {
                //2.老连接上有数据到来
                //  接收数据
                std::string buf;
                bool ret = output[i].RecvNonblock(&buf);
                if(!ret)
                {
                    es.DeleteFd(output[i].GetFd());
                    output[i].Close();
                    continue;
                }
                printf("recv data is %s\n", buf.c_str());

                buf.clear();
                buf.assign("wo jiu shi server");

                output[i].SendNonblock(buf);
            }
        }

    }

    listen_tcpsvr.Close();
    return 0;
}
