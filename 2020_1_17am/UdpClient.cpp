#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h> 
#include <strings.h>
void Usage(std::string proc_)
{
    std::cout<<"Usage: "<< proc_ << "server_ip server_port" <<std::endl;

}

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        Usage(argv[0]);
        exit(1);
    }
    
    int sock = socket(AF_INET,SOCK_DGRAM,0);
    if(sock<0)
    {
        std::cerr <<"sock error!"<<std::endl;
        exit(2);
    }


    std::string message;

    struct sockaddr_in server;  //server 端信息
    bzero(&server,sizeof(server)); // 将server端的前sizeof个信息全部清空0， 不建议使用 建议使用 memset
    
    server.sin_family = AF_INET;

    // argv[0] 服务端名称  argv[1] ip  argv[2] 端口  char* 类型
    server.sin_port =htons( atoi (argv[2]));
    server.sin_addr.s_addr = inet_addr(argv[1]);  // 1、必须是4字节 2、必须改成网络序列
    
    char buf[1024]; // 收到消息，往buf放

    for(;;)
    {
        socklen_t len = sizeof(server);//传入 参数大小  ， 传出 实际结构体大小
        std::cout << "Please Enter#"<<std::endl;
        std::cin >> message;
    
        sendto(sock,message.c_str(),message.size(),0,(sockaddr*)&server,sizeof(server));
        // &server ,收的时候，需要将服务器端的地址收来，
         // len  传入时代表 (struct sockaddr*)&server 参数的大小
       ssize_t s = recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&server,&len);
       buf[s] = 0;
       std::cout<<"server echo#"<< buf<<std::endl;
    }


    return 0;
}
