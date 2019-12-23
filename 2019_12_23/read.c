#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
int main()
{

   // 对命名管道操作方式与文件一样
   // 若只打开./read ----  open就会阻塞 
   //       因为此时管道myfifo 只有以读方式打开的 ，没有以写方式打开的 
   //       每有写操作，读操作就不能打开这个文件 --- 即 open会阻塞
   int fd = open("./myfifo",O_RDONLY);
   if(fd<0)
   {
       perror("reader open");
       return 1;
   }
 
   while(1)
   {
        char buf[1024] = {0};
        ssize_t n = read(fd,buf,sizeof(buf)-1);
        
        if(n<0)
        {
            perror("read");// read失败
            return 1;
        }
        if(n ==0)
        {
            // 所有写段关闭，读端已近读完了
            printf("read done!\n");
            return 0;
        }
        buf[n] = '\0';
        printf("[read] %s\n",buf);
   }

   close(fd);
    return 0;
}
