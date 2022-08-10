#include <iostream>

using namespace std;

class Father{
public:
    virtual void func() {
        cout<<"father func"<<endl;
        say();
    }
    void say(){
        cout<<"father say"<<endl;
    }

};

class Son : public Father {
public:
    void func() {
        cout<<"Son func"<<endl; //优先调用子类的say()，如果子类没有say()，那么会调用父类的say()
        say();
    }
    void say() { //如果直接用父类指针调用覆盖的非虚函数，会调用父类的say
        //func();
        cout<<"Son say"<<endl;
    }

};

int main() {
    Father * f = new Son();
    f->say();
    return 0;
}