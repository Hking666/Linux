#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
int main()
{


    int fd =  open("./myfifo",O_WRONLY);

    if(fd < 0)
    {
        perror("open");
        return 1;
    }
    
    while(1)
    {
        printf("---->");
        fflush(stdout);
        char buf[1024] ={0};
        // 让用户输入字符串到 buf ，然后再写
        read(0,buf,sizeof(buf)-1); // stdin 文件描述符为 0
        write(fd,buf,strlen(buf));
    }
    close(fd);
    return 0;
}
