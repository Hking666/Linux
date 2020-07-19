#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#define key 0x888888888
int main()
{
    int shmid =  shmget(key,1024,IPC_CREAT|0644);
    if(shmid<0)
    {
        return -1;
    }

    void* addr = shmmat(shmid,NULL,0);
    if(!addr)
    {
        return -1;
    }
    
    int count=0;
    while(1)
    {
        snprintf((char*)addr,1024,"%s--%d","linux--",count);
        sleep(2);
    }
    shmdt(addr);
    shmctl(shmid,IPC_RMID,NULL);
}
