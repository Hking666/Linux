#include <string.h>
#include "myshm.h"
int main()
{

    // 从共享内存中写数据
    // 1、创建/打开共享内存对象
    int shmid = Create();
    // 2、附加到共享内存对象上
    char* p = (char *)shmat(shmid,NULL,0);
    //3、直接使用
    strcpy(p,"hehehe\n");
    return 0;
}
