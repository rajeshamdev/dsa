// g++ addTwoNumbers.cpp -std=c++11
//
/**
 * You are given two non-empty linked lists representing two
 * non-negative integers. The digits are stored in reverse
 * order and each of their nodes contain a single digit.
 * Add the two numbers and return it as a linked list.

* You may assume the two numbers do not contain any leading
* zero, except the number 0 itself.

* Example:
* Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
* Output: 7 -> 0 -> 8
* Explanation: 342 + 465 = 807.
**/

#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x): val(x), next(NULL) {}
};

class Solution {
    public:
        ListNode* addTwoNumbers(ListNode *l1, ListNode *l2) {
            ListNode head(0);
            ListNode *l3 = &head;
            auto sum = 0;
            while (l1 || l2 || sum) {
                if (l1) sum += l1->val, l1 = l1->next;
                if (l2) sum += l2->val, l2 = l2->next;
                l3->next = new ListNode(sum%10);
                l3 = l3->next;
                sum /= 10;
            }
            return head.next;
        }
};

// This is added just to make sure code compiles.
// Tested on leetcode.
int
main() {
    Solution s1;
}
