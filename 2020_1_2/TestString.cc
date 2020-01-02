#include <iostream>
using namespace std;

int main()
{
    std::string s("hello,Linux");
    cout<<s<<endl;
    cout<<s.size()<<endl;
    cout<<s.capacity()<<endl;
    cout<<s.length()<<endl;

    cout<<"-----------------------------"<<endl;
    s.clear();
    cout<<s<<endl;
    
    cout<<"-----------------------------"<<endl;
    s.resize(20);
    cout<<s<<endl;
    cout<<s.size()<<endl;
    cout<<s.capacity()<<endl;
    cout<<s.length()<<endl;
    
    cout<<"-----------------------------"<<endl;
    s.resize(10,'a');
    cout<<s<<endl;
    cout<<s.size()<<endl;
    cout<<s.capacity()<<endl;
    cout<<s.length()<<endl;

    cout<<"-----------------------------"<<endl;
    s.resize(20,'a');
    cout<<s<<endl;

    s.push_back('b');
    cout<<s<<endl;

    return 0;
}
