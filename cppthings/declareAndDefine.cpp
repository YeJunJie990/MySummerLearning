#include <iostream>

using namespace std;

extern int  a; // 声明
extern int a = 2;   //任何包含了显示初始化的声明就成了定义
 
int main() {
    printf("%s\n",sizeof(A));
    return 0;
}