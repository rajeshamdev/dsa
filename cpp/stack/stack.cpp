#include <bits/stdc++.h>

using namespace std;

class Stack {
    private:
        int maxSize;
        unique_ptr<int[]> A;
        int top;
        bool empty(void) {return (top == -1 ? 1 : 0);}
        bool full(void) {return (top == maxSize - 1 ? 1 : 0);}
    public:
        Stack(int size) : maxSize(size)
        {
            A = unique_ptr<int[]>(new int[size]);
            top = -1;
        }
        void push(const int &val)
        {
            if (full()) {
                cout << "stack is full, cannot push data : " << val << " any more \n";
                return;
            }

            A[++top] = val;
        }
       
        int pop(void)
        {
            if (empty()) {
                cout << "stack is empty, cannot pop any more \n";
                return INT_MIN;
            }
            return A[top--];
        }
};

int main(void)
{
    Stack stk(5);
    for (int i = 0; i < 6; i++) {
        stk.push(i+1);
    }
    stk.pop();
    for (int i = 0; i < 6; i++) {
        stk.pop();
    }
}
