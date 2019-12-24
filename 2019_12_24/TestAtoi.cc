// c语言  字符串转整数
// 1. atoi
// 2. sprintf/sscanf

#include <stdio.h>
#include <stdlib.h>


int main()
{
/*
    char str[] ="100";
    int n = atoi(str);
    printf("%d\n",n);
    return 0;
*/


    char str[] ="100";
    int n = 0;
    sscanf(str,"%d",&n);
    printf("%d\n",n);

    return 0;
}
