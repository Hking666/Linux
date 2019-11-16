#include<stdio.h>
#include<unistd.h>
int main()
{
    const char* label ="/-\\|" ;
    // # 表示进度条
    char buf[1024]={0};
    int i = 0 ; 
    for( ;  i<100;++i)
    {
        buf[i] ='#';
        printf("[%d%%][%c][%s]\r",i,label[i%4],buf);
        fflush(stdout);
        usleep(500*1000);
    }
    return 0;
}
