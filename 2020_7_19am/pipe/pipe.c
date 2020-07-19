#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    int fd[2];
    int ret = pipe(fd);
    if(ret<0)
    {
        perror("pipe\n");
        return -1;
    }
    int count =0;
    while(1)
    {
        int ret = write(fd[1],"1",1);
        if(ret<0)
        {
            perror("write\n");
            return -1;
        }
        count++;
    }
    printf("count=%d\n",count);
}
