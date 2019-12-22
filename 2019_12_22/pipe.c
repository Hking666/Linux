#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    
    int fd[2];
    int ret = pipe(fd);

    if(ret<0)
    {
        perror("pipe");
        return 0;
    }
    //fd[0] -> 读数据
    //fd[1] -> 写数据
    pid_t pid = fork();
    if(pid > 0)
    {
            //father
        char buf[1024] = "hehe";
        write(fd[1],buf,strlen(buf));
      
        sleep(1);
        char buf_out[1024] ={0};
        ssize_t n = read(fd[0],buf_out,sizeof(buf_out)-1); // -1
        buf_out[n] = '\0';
        printf("child:%s\n",buf_out);
    }
    else if(pid ==0)
    {
            //child
        char buf_out[1024] ={0};
        ssize_t n = read(fd[0],buf_out,sizeof(buf_out)-1); // -1
        buf_out[n] = '\0';
        printf("child:%s\n",buf_out);
            
    }
    else
    {
        perror("fork:");
    }


    //管道使用完成之后，需要及时关闭文件描述符
    close(fd[0]);
    close(fd[1]);
    return 0;
}
