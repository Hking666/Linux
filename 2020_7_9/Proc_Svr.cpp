#include "tcpsvr.hpp"
#include <signal.h>
#include <sys/wait.h>
void sigcb(int signo)
{
    (void)signo;
    while(1)
    {
        waitpid(-1,NULL,WNOHANG);
    }
}
int main(int argc , char* argv[])
{

    if(argc!=3)
    {
        printf("Start Server : ./svr [ip] [port]");
        return 0;
    }

    signal(SIGCHLD,sigcb);

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

    while(1)
    {
        TcpSvr newSvr;
        struct sockaddr_in cliaddr;
        if(!svr.Accept(&cliaddr,&newSvr))
        {
            continue;// 一个连接失败不影响其他连接
        }

        printf("Have a new connect from cli:[ip]:%s [prot]:%d ",inet_ntoa(cliaddr.sin_addr),ntohs(cliaddr.sin_port));
        
        int pid = fork();
        if(pid<0)
        {
            perror("fork");
            exit(1);
        }
        else if(pid==0)
        {
            // child
            
            while(1)
            {
                std::string buf;
                newSvr.Recv(&buf);

                printf("client did say:%s\n",buf.c_str());

                printf("Please sent massage to client: ");
                fflush(stdout); 

                std::cin>>buf;
                newSvr.Send(buf);

            }
            newSvr.Close();
            exit(1);
        }
        else
        {
            // father
            newSvr.Close();

        }
        
    }


    
    return 0;
}
