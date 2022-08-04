#include <iostream>
#include <thread>
#include <string>
#include <queue>
#include <condition_variable>
#include <mutex>
#include <unistd.h>
using namespace std;

#define MAXNUM 10

struct task {
    int id;
    string data;
    task(int _id, string _data): id(_id), data(_data) { }
};


mutex mtx; //锁任务队列
condition_variable cdvarPro; //生产者条件变量
condition_variable cdvarCon; //消费者条件变量
queue<task> taskQ; //任务队列
int g_id = 0; //任务号


void Producer(int idx) {
    while (true) {
        {
            unique_lock<mutex> lk(mtx); //要加锁，因为要判断当前任务队列里是否有东西，即后面的taskQ.size()
            cdvarPro.wait(lk, [&](){return taskQ.size() < MAXNUM;}); //任务队列没满并且取得锁，往下执行向任务队列里放东西；否则释放锁，阻塞等待条件满足
            auto data = "producer" + to_string(idx) + " t" + to_string(g_id);
            printf("im producer %d, now producing conduct No%d\n", idx, g_id);
            task t(g_id++, data);
            taskQ.push(t);
        }
        cdvarCon.notify_one(); //任务队列已经有任务，通知一个消费者线程开始消费。这个条件变量不用被锁
        sleep(1);
    }
}

void Consumer(int idx) {
    while (true) {
        {
            unique_lock<mutex> lk(mtx); //消费者取任务，加锁，防止两个消费者取到相同的任务执行。
            cdvarCon.wait(lk, [&](){return !taskQ.empty();});
            task t = taskQ.front();
            taskQ.pop();
            printf("im consumer %d, now handling task No%d  ", idx, t.id);
            cout<<"its data: "<<t.data<<endl;
        }
        cdvarPro.notify_one();
        sleep(1);
    }
}

void LittlePool(int NUM_Producer, int NUM_Consumer){
    g_id = 0;
    vector<thread> ProducerThrs;
    vector<thread> ConsumerThrs;
    for (int i = 1; i <= NUM_Producer; i++) {
        ProducerThrs.emplace_back(Producer, i);
    }
    for (int i = 1; i <= NUM_Consumer; i++) {
        ConsumerThrs.emplace_back(Consumer, i);
    }
    for (int  i = 0; i < NUM_Producer; i++) {
        if (ProducerThrs[i].joinable()) ProducerThrs[i].join();
    }
    for (int  i = 0; i < NUM_Consumer; i++) {
        if (ConsumerThrs[i].joinable()) ConsumerThrs[i].join();
    }
}

int main() {
    LittlePool(5, 5);
    return 0;
}