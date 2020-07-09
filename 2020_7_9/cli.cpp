#include "tcpsvr.hpp"

int main(int argc,char* argv[])    
{

    while(argc!=3)
    {
        printf("Start Client: ./cil [ip] [port]");
        return 0;
    }

    std::string ip= argv[1];
    uint16_t port = atoi(argv[2]);

    
    TcpSvr cli;
    if(cli.CreatSocket())
    {
        return 0;
    }

    if(cli.Connect(ip,port))
    {
        return 0;
    }

    while(1)
    {
        printf("Please send to massage to : ");
        fflush(stdout);
        std::string buf;
        std::cin>>buf;
        cli.Send(buf);

        cli.Recv(&buf);
        printf("Server say: %s\n",buf.c_str());
    }

    cli.Close();
    return 0;
}
