#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main(int argc,char* argv[])
{
    
    //1. 先创建一个 socket 
    int sock = socket(AF_INET,SOCK_DGRAM,0);
    if(sock<0)
    {
        perror("socket");
        return 1;
    }
    
    // 2、 客户端一般不需要 bind
    //bind意味着与某个具体的端口号关联在一起
    //如果没有bind,操作系统会随机分配一个端口号
    //如果是服务器程序不去bind , 就会导致每次启动服务器的端口发生变化，客户端就没法连接了
    // 如果是客户端 bind 的话，可能出现问题
    // 通常情况下一个端口号只能被一个进程bind
    // 如果客户端 bind 一个端口号，其他客户有可能bind同一端口号，就会出错
    // 客户端让操作系统分配更科学
    
    // 2. 准备好服务器的 sockaddr_in 结构
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    server_addr.sin_port =htons(9090);


    while(true)
    {
        char buf[1024] = {0};
        printf("请输入一段内容：");
        fflush(stdout);
        scanf("%s",buf);
        sendto(sock,buf,strlen(buf),0,(sockaddr*)&server_addr,sizeof(server_addr));

        // 从服务器结束返回结果
        //
        char buf_output[1024] ={0};
        // 后面两个参数填 NULL 表示不关注对端的地址
        recvfrom(sock,buf_output,sizeof(buf_output)-1,0,NULL,NULL);
        
        printf("server resp:%s\n",buf_output);
    }
    return 0;
}
