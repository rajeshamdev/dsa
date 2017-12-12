#include <bits/stdc++.h>

using namespace std;
void klarge(int A[], int len, int k)
{
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < k; i++) {
        pq.push(A[i]);
    }
    for (int i = k; i < len; i++) {
        if (A[i] > pq.top()) {
            pq.pop();
            pq.push(A[i]);
        }
    }
    for (int i = 1; i <= k; i++) {
        cout << pq.top() << ", ";
        pq.pop();
    }
    
}

int main(void)
{
    int A[] = {1, 23, 12, 9, 30, 2, 50};
    int k = 3;
    klarge(A, sizeof(A)/sizeof(A[1]), k);
    cout << "\n";

    int V[] = {1, 23, 12, 9, 30, 2, 50};
    sort(V, .rbegin(), V.rend());
    for (int i : V) {
        cout << i << ", ";
    }
    cout << "\n";
}
