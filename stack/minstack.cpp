#include <bits/stdc++.h>
using namespace std;

class custumStack {
    private:
        stack<int> stk;
        int min;
    public:
        void push(const int &val)
        {
            if (stk.empty()) {
                stk.push(val);
                min = val;
            } else if (val < min) {
                stk.push(2*val-min);
                min = val;
            } else {
                stk.push(val);
            }
        }
        int pop(void)
        {
            if (stk.empty()) return INT_MAX;
            int t = stk.top();
            stk.pop();
            if (t < min) {
                int res = min;
                min = 2*min - t;
                t = res;
            }
            return t;
        }
        int getMin(void)
        {
            if (stk.empty()) return INT_MAX;
            else return min;
        }
};

int main(void)
{
    custumStack stk;
    stk.push(10);
    stk.push(3);
    stk.push(9);
    stk.push(2);
    stk.push(12);
    for (int i = 0; i < 5; i++) {
        cout << "min: " << stk.getMin() << "\n";
        cout << "popped: " << stk.pop() << "\n";
    }
}
