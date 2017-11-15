/**
 * Demonstration of producer/consumer problem with mutex/condvar.
 * g++ -g -std=c++11 producerConsumer.cpp -lpthread
 */

#include <iostream>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <chrono>
#include <thread>

using namespace std;

class boundQueue {
    private:
        mutex mu;
        condition_variable cv_qfull; // wait when queue is full
        condition_variable cv_qempty; // wait when the queus is empty
        queue<int> bq;
        int qsize;
    public:
        void put(int data);
        int get(void);
        int size(void) {return qsize;}
        boundQueue(int size) : qsize(size) {}
};

void boundQueue::put(int data)
{
    unique_lock<mutex> plock(mu);
    cv_qfull.wait(plock, [this](){return bq.size() < qsize;});
    bq.push(data);
    cout << "producer, pushed data: " << data << "\n";
    plock.unlock();
    cv_qempty.notify_one();
}


int boundQueue::get(void)
{
    unique_lock<mutex> conlock(mu);
    cv_qempty.wait(conlock, [this](){return bq.size() > 0;});
    int data = bq.front();
    bq.pop();
    cout << "consumer, poped data: " << data << "\n";
    conlock.unlock();
    cv_qfull.notify_one();
    return data;
    
}

void producer(boundQueue &bq)
{
    int i = 0;
    while (i < bq.size()) {
        bq.put(i);
        this_thread::sleep_for(chrono::milliseconds(100));
        ++i;
    }
} 

void consumer(boundQueue &bq)
{
    int i = 0;
    while (i < bq.size()) {
        int data = bq.get();
        this_thread::sleep_for(chrono::milliseconds(250));
        ++i;
    }
}

int main(void)
{
    boundQueue bq(10);
    thread t1(producer, ref(bq)); 
    thread t2(consumer, ref(bq)); 
    t1.join();
    t2.join();
}
