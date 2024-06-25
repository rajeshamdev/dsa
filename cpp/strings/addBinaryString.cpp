/**
 * Given two binary strings, return their sum (also a binary string).
 * The input strings are both non-empty and contains only characters 1 or 0.
 *
 * Example 1:
 * Input: a = "11", b = "1"
 * Output: "100"
 *
 * Example 2:
 * Input: a = "1010", b = "1011"
 * Output: "10101"
 *
 * Constraints:
 *
 * Each string consists only of '0' or '1' characters.
 * 1 <= a.length, b.length <= 10^4
 * Each string is either "0" or doesn't contain any leading zero.
 */

#include <string>
#include <iostream>

using namespace std;

class Solution {
public:
    string addBinary(string a, string b) {
        string ans = "";

        int carry = 0, apos = a.size() - 1, bpos = b.size() - 1;
        while (apos >= 0 || bpos >= 0 || carry) {
            carry += apos >= 0 ? (a[apos--] - '0') : 0;
            carry += bpos >= 0 ? (b[bpos--] - '0') : 0;
            ans += carry % 2 + '0';
            carry /= 2; 
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};

int
main(void)
{
    Solution s1;
}
