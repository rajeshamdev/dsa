class Solution {
public:
    int myAtoi(string str)
    {
        auto len = str.size();
        if (0 == len) return 0;
        auto i = 0;
        auto multi = 1;
        while (str[i] == ' ') i++;
        if (str[i] == '+') {multi = 1; i++;}
        else if (str[i] == '-') {multi = -1; i++;}
        long res = 0;
        while (isdigit(str[i])) {
            res = res*10 + str[i]-'0';
            if (res*multi > INT_MAX) return INT_MAX;
            if (res*multi < INT_MIN) return INT_MIN;
            i++;
        }
        return res*multi;
    }
};
