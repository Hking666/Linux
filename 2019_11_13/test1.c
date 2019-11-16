#include<stdio.h>

void Func3()
{
    printf("hello Linux!!!");
    printf("hello Linux!!!");
    printf("hello Linux!!!");
    printf("hello Linux!!!");

}
void Func2()
{
    Func3();
}
void Func1()
{
    int num = 10;
    int count = 20;
    Func2();
}
int main()
{
    int i = 0;
    
    for(i = 0 ; i < 5 ; ++i)
    {
        printf("%d",i);
    
    }

    Func1();
    return 0;
}
