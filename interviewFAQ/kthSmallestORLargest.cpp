#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/**
 *  1. Create a max heap with 'k' number of elements - O(logk)
 *  2. Walk throught the remaining elements of the list. If any
 *     of this element is smaller than top of the queue then
 *     replace the top.
 *  Step-1 takes O(logk) time and Step-2 takes O(n).
 *
 *  Time complexity : O(nlogk);
 */
int KthSmallest(const vector<int> &vec, int k)
{
    if (vec.size() < k) return 0;

    priority_queue<int, vector<int>, less<int> > pq;
    for (int i = 0; i < k; i++) {
        pq.push(vec[i]);
    }

    for (int i = k; i < vec.size(); i++) {
        if (vec[i] < pq.top()) {
            pq.pop();
            pq.push(vec[i]);
        }
    }
    return pq.top();
}

/**
 * 1. Create min heap of size 'k'.
 * 2. walk through remaining list elements. If any of it is greater than
 *    top of the queue, replace queue top element.
 * 3. Top of the element is 'k'th largest element.
 *
 * Time complexity : O(nlogk);
 */
int KthLargest(const vector<int> &vec, int k)
{
    if (vec.size() < k) return 0;
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < k; i++) {
        pq.push(vec[i]);
    }
    for (int i = k; i < vec.size(); i++) {
        if (vec[i] > pq.top()) {
            pq.pop();
            pq.push(vec[i]);
        }
    }
    return pq.top();
}

int main(void)
{
    vector<int> v {7, 4, 6, 3, 9, 1};
    int kthSmallest = KthSmallest(v, 3); 
    cout << "Kth smallest : " << kthSmallest << "\n";

    int kthLargest = KthLargest(v, 3); 
    cout << "Kth largest : " << kthLargest << "\n";

    return 0;
}
