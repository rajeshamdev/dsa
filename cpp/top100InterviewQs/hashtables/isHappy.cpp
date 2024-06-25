class Solution {
public:
    // Based on the fact that all unhappiness goes through 4
    bool isHappy1(int n)
    {
        int sum = 0;
        while (n > 4) {
            while (n) { sum += (n%10) *(n%10); n /= 10;}
            n = sum, sum = 0;
        }
        return (n == 1);
    }
    
    // Floy's cycle detection
    bool isHappy(int n)
    {
        int slow = next(n);
        int fast = next(next(n));
        while (slow != fast) {
            slow = next(slow);
            fast = next(next(fast));
        }
        return slow == 1;
    }
    int next(int n)
    {
        int sum = 0;
        while (n) {sum += ((n%10) *(n%10)); n/=10;}
        return sum;
    }
};
