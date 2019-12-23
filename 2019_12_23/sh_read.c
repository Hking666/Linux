
#include "myshm.h"

int main()
{

    // 从共享内存中读数据
    //
    //1 创建共享内存对象
    int shmid = Create();
    
    //2 附加到共享内存对象上
    char* p = (char*)shmat(shmid,NULL,0);

    printf("read:%s\n",p);
    
    return 0;
}
