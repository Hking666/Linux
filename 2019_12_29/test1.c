#include <stdio.h>
#include <unistd.h>
#include <string.h>


int main()
{

    int i =0;
    char buf[102];
    memset(buf,'\0',sizeof(buf));
    const char *lable="|/-\\";
    while(i<=100)
    {
      printf("[%-100s][%d%%][%c]\r",buf,i,lable[i%4]);
      fflush(stdout);
      buf[i++]='#';
      usleep(100000);
    
    }
    return 0;
}
