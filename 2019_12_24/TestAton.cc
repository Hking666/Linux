#include <iostream>
using namespace std;
#include <sstream>
#include <string>
int main()
{
    //1、stringstream 
    std::stringstream ss;
    std::string str = "100";
    int num = 0;
    ss<<str;
    ss>>num;
    cout<<num<<endl;

    //2、std::stoi
    string str1 ="200";
    int num1 = std::stoi(str1);
    cout<<num1<<endl;

    //3. boost
    

    return 0;
}
