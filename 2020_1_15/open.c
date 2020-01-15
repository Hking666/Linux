#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{

    int fd = open("file1",O_WRONLY|O_CREAT,0664);
    if(fd<0)
    {
        perror("open");
        return 1;
    }
    printf("fd = %d \n",fd);

    char buf[]="hello world!!!";
    int writeSize = write(fd,buf,sizeof(buf)-1);
    if(writeSize<0)
    {
        perror("write");
        return 2;
    }
    printf("writeSize = %d\n ",writeSize);
//    while(1)
//    {
//        sleep(1);
//    }
//
    
    lseek(fd,0,SEEK_SET);
    char redBuf[1024];
    memset(redBuf,'\0',sizeof(redBuf));

    int readSize = read(fd,redBuf,sizeof(redBuf)-1);
    if(readSize<=0)
    {
        perror("read\n");
        return 3;
    }
    printf("redBuf:%s",redBuf);
    return 0;
}
