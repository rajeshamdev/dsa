#include <iostream>
#include <thread>
#include <queue>

using namespace std;

class BoundQueue {
    private:
        mutex queueLock;
        condition_variable queueCv;
        queue <int> sharedQueue;
        int maxQueueSize;
        void producer(int);
        void consumer(void);
    public:
        BoundQueue(int size) : maxQueueSize(size) {}
        void run(void);
};

void
BoundQueue::producer(int n)
{
    int count = 10;
    while (count--) {
        unique_lock<mutex> ql(queueLock);
        queueCv.wait(ql, [this]{return sharedQueue.size() < maxQueueSize;});
        sharedQueue.push(n++);
        ql.unlock();
        queueCv.notify_all();
    }
}

void
BoundQueue::consumer(void)
{
    int count = 10;
    while (count--) {
        unique_lock<mutex> ql(queueLock);
        queueCv.wait(ql, [this]{return !sharedQueue.empty();});
        int readval = sharedQueue.front();
        cout << "Popped : " << readval << "\n";
        sharedQueue.pop();
        ql.unlock();
        queueCv.notify_all();
    }
}

void
BoundQueue::run(void)
{
    thread t1(&BoundQueue::producer, this, 10);
    thread t2(&BoundQueue::consumer, this);
    t1.join();
    t2.join();
}

int
main(void)
{
    BoundQueue boundQueue(5);
    boundQueue.run();
    return 0;
}
