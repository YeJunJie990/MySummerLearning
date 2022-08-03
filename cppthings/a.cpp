#include <iostream>
#include <string.h>
#include <memory>
using namespace std;

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

int main() {
    testSharePtr();
    return 0;
}