#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x): val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* reverseList(ListNode *head)
    {
        ListNode *new_head = nullptr;
        while (head) {
        ListNode *tmp = head;
        head = head->next; // moves forward the head.
        tmp->next = new_head;
        new_head = tmp;
        }
        return new_head;
    }
};

int
main(void)
{
    Solution s1;
}

