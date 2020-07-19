#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main()
{

    int fd[2];
    if(pipe(fd)<0)
    {
        perror("pipe\n");
        return 0;
    }

    int flag = fcntl(fd[0],F_GETFL);
    flag |= O_NONBLOCK;
    fcntl(fd[0],F_SETFL,flag); //将读设置为非阻塞
    char buf[1024]={0};
    while(1)
    {
        int ret = read(fd[0],buf,sizeof(buf)-1);//会一直写，直到资源不可用
        if(ret<0)
        {
            perror("buf"); 
            return ret;
        }

    }


    return 0;
}
