#include <iostream>
#include <string.h>
#include <memory>
#include <vector>
#include <set>
#include <unordered_set>
#include <deque>
#include <queue>
#include <list>
using namespace std;

/*
    shared_ptr的循环引用
*/
class B;

class A{
public:
    shared_ptr<B> pb_;
    ~A(){
        printf("deconstruction of A\n");
    }
};

class B{
public:
    shared_ptr<A> pa_;
    ~B(){
        printf("deconstruction of B\n");
    }
};

void testSharePtr() {
    auto ptrA = make_shared<A>();
    auto ptrB = make_shared<B>();
    cout<<"ptrA conut: "<<ptrA.use_count()<<endl;
    cout<<"ptrB conut: "<<ptrB.use_count()<<endl;
    ptrA->pb_ = ptrB;
    ptrB->pa_ = ptrA;
    cout<<"ptrA conut: "<<ptrA.use_count()<<endl;
    cout<<"ptrB conut: "<<ptrB.use_count()<<endl; //永远不可能析构A和B,由此造成内存泄漏
}


/*
    测试vector的emplace_back和push_back
*/
class testDemo
{
public:
    testDemo(int num):num(num){
        std::cout << "调用构造函数" << endl;
    }
    testDemo(const testDemo& other) :num(other.num) {
        std::cout << "调用拷贝构造函数" << endl;
    }
    testDemo(testDemo&& other) :num(other.num) {
        std::cout << "调用移动构造函数" << endl;
    }
private:
    int num;
};

void testVector()
{
    cout << "emplace_back:" << endl;
    std::vector<testDemo> demo1;
    demo1.reserve(100);
    demo1.emplace_back(2);  

    cout << "push_back:" << endl;
    demo1.push_back(2);

    // emplace_back:
    // 调用构造函数
    // push_back:
    // 调用构造函数
    // 调用移动构造函数
}

/*
    测试迭代器
*/
void testIt() {
    unordered_set<int> mySet = {1,2,3,4,5};
    auto itset = mySet.begin();
    while (itset != mySet.end()) cout<<*itset++<<endl; 
    //itset--; 前向迭代器，编译不通过
    deque<int> dq = {1,2,3,4,5};
    auto itdq = dq.begin();
    while (itdq != dq.end()) cout<<*itdq++<<endl;
    //itdq--;
    //dq.at(1); 随机访问迭代器
    list<int> mylist = {1,2,3,4,5};
    auto itlist = mylist.begin();
    while (itlist != mylist.end()) cout<<*itlist++<<endl;
    //itlist--;
    //cout<<*itlist<<endl; 双向迭代器，可前可后
}

void testConst() {
    int a = 10;
    int * const p = &a; //顶层const，p的指向不可以改变
    *p = 12;
    cout<<*p<<endl;
    const int * p1 = &a; //底层const，无法通过p1修改a的值
    //*p1 = 13;
    cout<<*p1<<endl;
}

void func(int a[], int* a1) {
    cout<<a[0]<<endl;
    cout<<a[1]<<endl;
    cout<<a1[0]<<endl;
    cout<<a1[1]<<endl;
    cout<<*(++a1)<<endl;
    cout<<*(++a1)<<endl;
    cout<<*(a++)<<*a<<endl;
}

void testCVec() {
    int a[2] = {2,3};
    func(a, a);
}

class F {
public:
    virtual void fun(int a) { // 虚函数
        cout << "This is F fun " << a << endl;
    }  
    void add(int a, int b) {
        cout << "This is F add " << a + b << endl;
    }
};

// 子类
class S: private F {
public:
    void fun(int a) override {  // 覆盖
        cout << "this is S fun " << a << endl;
    }
    void add(int a) {   // 隐藏
        cout << "This is S add " << a + a << endl;
    }
};

void testHidden() {
    // 基类指针指向派生类对象时，基类指针可以直接调用到派生类的覆盖函数，也可以通过 :: 调用到基类被覆盖
    // 的虚函数；而基类指针只能调用基类的被隐藏函数，无法识别派生类中的隐藏函数。
    F *p = new S();
    p->fun(1);      // 调用子类 fun 覆盖函数
    p->F::fun(1);   // 调用父类 fun
    p->add(1, 2);

    //S *p1 = new S();
    p1->F::fun(10);
    //p->add(1);      // 错误，识别的是 A 类中的 add 函数，参数不匹配
    //p->S::add(1);
}

int main() {
    //testSharePtr();
    //testVector();
    //testIt();
    testCVec();
    
    return 0;
}