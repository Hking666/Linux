#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
int main()
{

    int fd =open("myflie1",O_CREAT|O_RDWR,0644);
    if(fd<0)
    {
        perror("open");
        return 1;
    }

    close(1);
    dup2(fd,1);
    for(;;)
    {
        char buf[1024];
        memset(buf,'\0',sizeof(buf));
        ssize_t read_size = read(0,buf,sizeof(buf)-1);
        if(read_size<0)
        {
            perror("read");
            break;
        }
    
        printf("%s",buf);
        fflush(stdout);
    }
    return 0;
}
