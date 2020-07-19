#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>


int main()
{
    int fd = open("./fifo",O_RDONLY);
    if(fd<0)
    {
        perror("open");
        return 0;
    }

    char buf[1024]={0};
    int ret  = write(fd,buf,sizeof(buf)-1);
    if(ret<0)
    {
        perror("write");
            return 0;
    }
    close(fd);
    return 0;
}

