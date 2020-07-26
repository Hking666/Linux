#include <iostream>
#include <math.h>
#include <vector>
using namespace std;
bool pernum(int n)  //求出所有约数（不包含本身，重复的只算一次，例如36的约数只有一个6）
{
    int sum=1;
    for(int i=2;i<=sqrt(n);i++)
    {
        if(n%i==0)
        {
            sum+=i;
            if(i!=(n/i))
                sum+=(n/i);

        }

    }
    if(sum==n)
        return true;
    else
        return false;

}
int main()
{
    int n;
    while(cin>>n)
    {
        int num=0;
        if(n<=1)
            return -1;
        for(int i=2;i<=n;i++)//从2开始计算是否是完美数的个数
        {
            if(pernum(i))
                num++;

        }
        cout<<num<<endl;

    }
    return 0;

}
