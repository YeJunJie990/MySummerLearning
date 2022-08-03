#include<iostream>
#include<stdio.h>
#include<atomic>

using namespace std;

/*
class Counter
{
public:
    Counter(): refCounter(0) {}

    void add(){++refCounter;}

    void sub(){--refCounter;}
    
    void setval(int x) {refCounter.store(x);}

    int get() const{return refCounter;}

private:
    std::atomic<int> refCounter;
};


template <class T>
class mySharedPointer{
    //这个实现不是完美的
    //共享指针的计数器是共享的。指向的内存也是共享的。

    //每个赋值语义，都要对当前this指针指向的内存的指针数量都要减1，如果最后只剩一个共享指针，
    //那么还需要释放所指向的内存。在这之后才进行指向的改变。
    //这也是为什么下面的完美的版本会有一个clear函数。

    //在实现每个移动语义时，会将被移动共享指针的计数器指针进行nullptr，
    //这就要注意在析构时，要判断当前计数器指针是否为空。
private:
    Counter* pRefCount;
    T* obj;
public:
    mySharedPointer(): obj(nullptr), pRefCount(new Counter()) {}
    mySharedPointer(T* source): obj(source), pRefCount(new Counter()){
        //cout<<"constructor"<<endl;
        pRefCount->setval(1);
    }
    mySharedPointer(const mySharedPointer<T> & source) {
        pRefCount = source.pRefCount;
        pRefCount->add();
        obj = source.obj;
    }
    mySharedPointer(mySharedPointer<T> && source) {
        //移动语义是指针的转移，所以这里要把指针置空
        this->obj = source.obj;
        source.obj = nullptr;
        this->pRefCount = source.pRefCount;
        source.pRefCount = nullptr;
    }
    T& operator*(){
        return *obj;
    }
    T* operator->() {
        return obj;
    }
    mySharedPointer<T>& operator= (const mySharedPointer<T> & source){
        obj = source.obj;
        pRefCount = source.pRefCount;
        pRefCount->add();
        return *this;
    }
    T* get(){
        return obj;
    }
    int count() {
        return pRefCount->get();
    }
    ~mySharedPointer() {
        //cout<<"deconstructor"<<endl;
        if (pRefCount){ 
            //因为实现了移动语义，如果某个共享指针触发了移动语义，那么它的计数器指针会被悬空，
            //所以析构的时候要判断计数器指针是不是为空
            pRefCount->sub();
            if (pRefCount->get() == 0) {
                delete obj;
                obj = nullptr;
                delete pRefCount;
                pRefCount = nullptr;
            }
        }
    }
};

int main () {
    mySharedPointer<int> ptr1(new int(1));
    cout<<"ptr1 count: "<< ptr1.count() << ", ptr1 address: "<< *ptr1.get()<< endl;

    auto ptr2(ptr1);
    *ptr2 = 10;
    cout<<"ptr2 count: "<< ptr2.count() << ", ptr2 address: "<< *ptr2.get()<< endl;

    {
        auto ptr3 = ptr1;
        *ptr3 = 100;
        cout<<"ptr3 count: "<< ptr3.count() << ", ptr3 address: "<< *ptr3.get()<< endl;
    }

    auto ptr4 = ptr1;
    *ptr4 = 1000;
    cout<<"ptr4 count: "<< ptr4.count() << ", ptr4 address: "<< *ptr4.get()<< endl;

    auto ptr5(move(ptr4));
    *ptr5 = 10000;
    cout<<"ptr5 count: "<< ptr5.count() << ", ptr5 address: "<< *ptr5.get()<< endl;
    return 0;
}
*/


class PtrCounter
{
public:
    PtrCounter(): count{0} {}

    void add(){++count;}

    void subtract(){--count;}

    int get() const{return count;}

private:

    std::atomic<int> count;
};

template<typename T>
class SharePtr
{
    // 比较好的版本，通过原子操作实现计数器
    // 如果不通过原子操作，那么在每次对计数器操作的时候，都需要对计数器加锁
public:
    SharePtr(T* ptr) : my_ptr{ptr}, my_ref_count{new PtrCounter} {my_ref_count->add();}
    SharePtr() : my_ptr(nullptr),my_ref_count(new PtrCounter){}

    SharePtr(const SharePtr &p)
    {
        this->my_ptr = p.my_ptr;
        this->my_ref_count = p.my_ref_count;
        my_ref_count->add();
    }

    SharePtr& operator = (const SharePtr &p)
     

    SharePtr(SharePtr &&p)
    {
        this->my_ptr = p.my_ptr;
        this->my_ref_count = p.my_ref_count;
        p.my_ptr = nullptr;
        p.my_ref_count = nullptr;
    }

    SharePtr &operator =(SharePtr &&p)
    {
        clear();
        this->my_ptr = p.my_ptr;
        this->my_ref_count = p.my_ref_count;
        p.my_ptr = nullptr;
        p.my_ref_count = nullptr;
        return *this;
    }
    ~SharePtr(){clear();}

    int use_count() {return my_ref_count->get();}

    T* get() const {return my_ptr;}
    T* operator->() const {return *my_ptr;}
    T& operator*() const {return *my_ptr;}
    operator bool() const {return my_ptr;}

private:
    T* my_ptr;
    PtrCounter* my_ref_count;

    void clear() //每个移动和赋值语义都要用到这个，判断是否需要当前this共享指针指向的区域
    {
        if(my_ref_count) //因为实现了移动语义，移动后的共享指针的计数器指针被置为空，所以要判断是否为空
        {
            my_ref_count->subtract();
            if(my_ref_count->get() == 0)
            {
                if(my_ptr) delete my_ptr;
                delete my_ref_count;
            }
        }
    }
};


int main () {
    SharePtr<int> ptr1(new int(1));
    cout<<"ptr1 count: "<< ptr1.use_count() << ", ptr1 address: "<< *ptr1.get()<< endl;

    auto ptr2(ptr1);
    *ptr2 = 10;
    cout<<"ptr2 count: "<< ptr2.use_count() << ", ptr2 address: "<< *ptr2.get()<< endl;

    {
        auto ptr3 = ptr1;
        *ptr3 = 100;
        cout<<"ptr3 count: "<< ptr3.use_count() << ", ptr3 address: "<< *ptr3.get()<< endl;
    }

    auto ptr4 = ptr1;
    *ptr4 = 1000;
    cout<<"ptr4 count: "<< ptr4.use_count() << ", ptr4 address: "<< *ptr4.get()<< endl;

    auto ptr5(move(ptr4));
    *ptr5 = 10000;
    cout<<"ptr5 count: "<< ptr5.use_count() << ", ptr5 address: "<< *ptr5.get()<< endl;
    return 0;
}

