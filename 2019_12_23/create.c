// 创建共享内存对象
//1
#include "myshm.h"
int Create()
{

    key_t k = ftok(".",0x1);
    if(k == -1)
    {
        perror("tok");
        return 1;
    }
    printf("key = %d\n",k);
    
    int ret = shmget(k,1024,IPC_CREAT|IPC_EXCL);// 存在即直接打开，不存在创建
    
    if(ret < 0)
    {
        perror("shmget");
        return -1;
    }
    printf("ret = %d\n",ret);
    return ret;
}

int main()
{
    Create();
    return 0;
}
