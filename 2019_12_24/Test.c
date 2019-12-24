#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>

int main()
{
    int fd[2] ={0};
    pipe(fd);
    close(fd[0]);
    write(fd[1],"hehe",4);
    printf("write done!\n");
    return 0;

}

