#include <bits/stdc++.h>
using namespace std;

/**
 * http://blog.gainlo.co/index.php/2016/12/23/uber-interview-questions-permutations-parentheses/?utm_source=glassdoor&utm_campaign=glassdoor&utm_medium=122216
 *
 *
 * Better way to denote a sub-problem is use two variables (left, right),
 * which indicates how many left/right parenthesis left. So we can have
 * the following algorithm:
 * 
 *  We start with left = n and right = n and an array results to store parentheses.
 *  As long as left > 0, we can always append “(“ to results, then the problem becomes (left – 1, right).
 *  When left < right, we can also append “)” to results, then the problem becomes (left, right – 1).
 *  When left = right = 0, we can print results.
 * 
 *  Note, left should never be greater than right.
 */


void pm(int open, int close, string s)
{
    if (open == 0 && close == 0) {
        cout << s << "\n";
        return;
    }

    if (open > 0)
        pm(open-1, close, s+'(');
    if (open < close)
        pm(open, close-1, s+')');
}
int main(void)
{
    int n = 3;
    pm(n, n, "");
}
