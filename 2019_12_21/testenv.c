#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc,char*argv[] ,char* env[] )
{

    int i = 0;
    for(;env[i];i++)
    {
        printf("%s\n",env[i]);
    }

    printf("********************\n");

    extern char **environ;//char *env[]    char **environ = &env
    i = 0;
    for(;environ[i];++i)
    {
        printf("%s\n",environ[i]);
    }
    

    return 0;
}
