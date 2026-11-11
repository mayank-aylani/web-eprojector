//Multithreading
#include<thread>
#include<iostream>
using namespace std;
void func()
{
for(int i=1;i<=200;++i) cout<<i<<" ";
}
int main()
{
thread t(func);
for(int j=601;j<=640;++j) cout<<j<<" ";
t.join();
return 0;
}