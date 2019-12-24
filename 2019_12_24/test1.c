#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
//kill模拟实现
int main(int argc , char *argv[])
{
    // kill -9 110
    //为了简单，只处理一个进程
    if(argc != 3)
    {
      //  printf("参数有误！。/mykill [signal] [pid]\n");
        return 1;
    }
    
    // argv[1] => -9   将字符串转换成  整数
    int signo =atoi( argv[1]+1);
    pid_t pid = atoi(argv[2]);
    int ret = kill(pid,signo);
    if(ret < 0)
    {
        perror("kill");
        return 1;
    }
    
    return 0;
}
