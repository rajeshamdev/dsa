#include <iostream>
#include <mutex>
#include <queue>
#include <condition_variable>

using namespace std;

class Queue {
private:
    mutex mu;
    condition_variable cv_qempty; // wait when queue is empty
    queue<int> bq;
public:
    void put(int data)
    {
        // ASSUMPTION: queue size is unlimited, therefore we
        // dont need to check for queue full. If we were to
        // check for queue full, we would have needed another cond var.
        unique_lock<mutex> plock(mu);
        bq.push(data); // queue is shared resource and protected.
        cout << "producer pushed data onto queue : " << data << "\n";
        plock.unlock();
        cv_qempty.notify_one(); // assumptiom: only one consumer. If not use notify_all().
    }

    int get(void)
    {
        unique_lock<mutex> conlock(mu);
        // wait on empty queue.
        cv_qempty.wait(conlock, [this](){return bq.size() != 0;});
        int data = bq.front();
        bq.pop();
        cout << "consumer popped data from queue : " << data << "\n";
        conlock.unlock();
        return data;
    }
};
