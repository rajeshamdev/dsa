/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* reverseList(ListNode* head)
    {
        ListNode *r = nullptr;
        while (head) {
            ListNode *p = head;
            head = head->next;
            p->next = r;
            r = p;
        }
        return r;
    }
};
