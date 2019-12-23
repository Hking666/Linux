#pragma once
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
static int Create()
{

    key_t k = ftok(".",0x2);
    if(k == -1)
    {
        perror("tok");
        return 1;
    }
    printf("key = %d\n",k);
    
    int ret = shmget(k,1024,IPC_CREAT|0666);// 存在即直接打开，不存在创建
    
    if(ret < 0)
    {
        perror("shmget");
        return 1;
    }
    printf("ret = %d\n",ret);
    return ret;
}
