#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    close(0);
    int fd = open("myfile1",O_RDONLY|O_CREAT);
    if(fd<0)
    {
        perror("open");
        return 1;
    }

    printf("fd= %d\n",fd);
    close(fd);
    return 0;
}
