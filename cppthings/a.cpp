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

int main() {
    //testSharePtr();
    testVector();
    //testIt();
    return 0;
}