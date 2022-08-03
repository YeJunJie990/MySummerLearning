#include <iostream>

using namespace std;

extern int  a; // 声明

class A{
    public:
        double a; //8
        char b; 
        int c; 
        char d; 
        int f;
        //sizeof（A） = 24
}; //定义， 类内的成员变量符合内存对齐

/*
Char 
偏移量必须为sizeof(char)即1的倍数 
int 
偏移量必须为sizeof(int)即4的倍数 
float 
偏移量必须为sizeof(float)即4的倍数 
double 
偏移量必须为sizeof(double)即8的倍数 
Short 
偏移量必须为sizeof(short)即2的倍数 
各成员变量在存放的时候根据在结构中出现的顺序依次申请空间，同时按照上面的对齐方式调整位置，空缺的字节VC会自动填充。
且总的字节数为结构体中占用最大空间的类型所占用的字节数的倍数
*/

class B; //申明
 
int main() {
    //int a; //定义
    A a;
   //B b;
    //cout<<sizeof(b)<<endl;
    cout<<sizeof(A)<<endl;
    return 0;
}