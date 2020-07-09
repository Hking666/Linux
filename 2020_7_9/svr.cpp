#include "tcpsvr.hpp"

int main(int argc ,char* argv[])
{
    while(argc != 3)
    {
        printf("Start svr : ./svr [ip] [port]\n");
    }

    std::string ip = argv[1];
    uint16_t port = atoi(argv[2]);

    TcpSvr svr;
    if(!svr.CreatSocket())
    {
        return 0;
    }

    if(!svr.Bind(ip,port))
    {
        return 0;
    }

    if(!svr.Listen())
    {
        return 0;
    }

    TcpSvr  newsvr;//输出参数   接收accep函数 产生的新的 sockfd
    struct sockaddr_in clientAddr; // 输出参数 接收客户端的地址信息，用于给对端发送数据

    if(!svr.Accept(&clientAddr,&newsvr))
    {
        return 0;
    }

    while(1)
    {
        std::string buf;
        newsvr.Recv(&buf);
        printf("client say:%s\n",buf.c_str());

        printf("please return to client massage: ");
        fflush(stdout);
        std::cin>>buf;

        newsvr.Send(buf);
    }
    newsvr.Close();
    svr.Close();
    return 0;
}

