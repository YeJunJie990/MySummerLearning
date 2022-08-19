#include <bits/stdc++.h>

using namespace std;

class A {
public: 
    int get_x() const { //如果函数不会改变成员变量，那么要加const，否则， 如果外部定义了一个const对象，是没有
    //办法通过该对象调用到该非const函数的。 int get_x() {return x;} （编译错误）
        return x;
    }
    int get_y() const {
        return y;
    }
    A(int _x = 0, int _y = 0) : x(_x), y(_y) {};
    A(const A & _a);
    int x, y;
};

 vector<int> * const getVec() {
    //vector<int> a(1000000);//这样不行，编译错误，因为a是局部变量，函数结束即销毁
    vector<int> * a = new vector<int>(1000000); 
    //return *a; //这样不能用引用返回，会造成内存泄漏，因为无法通过返回的引用，释放掉堆中的空间
    return a;            //只能传递指针，然后在申请处delete
}

class WonderfulClass
{
public:
       static WonderfulClass* makeAnObject(){ //类内成员函数可以访问到private成员
            // 创建一个WonderfulClass对象并返回其指针
            return new WonderfulClass();
       }
private:
       WonderfulClass() { cout<<"-------"<<endl;}
};
 

void test1() {
    auto a = getVec();
    cout<<a->size()<<endl;
    delete a;
}

void test2() {
    WonderfulClass *p = WonderfulClass::makeAnObject();
    //打印-----------------
    delete p; 
}


int main() {
    //test1();
    test2();
    return 0;
}