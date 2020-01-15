#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    close(1);
    int fd = open("myfile2",O_WRONLY|O_CREAT,0644);
    if(fd<0)
    {
        perror("open");
        return 1;
    }
    printf("fd:%d\n",fd);
    fflush(stdout);

    close(fd);
    
    return 0;
}
