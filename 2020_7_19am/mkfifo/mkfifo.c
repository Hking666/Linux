#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
int main()
{
    mkfifo("./fifo",0664);

    int fd = open("./fifo",O_WRONLY);
    if(fd<0)
    {
        perror("open");
    }
    int ret  = write(fd,"nihao",5);
    if(ret<0)
    {
        perror("write");
        return 0;
    }
    return 0;
}
