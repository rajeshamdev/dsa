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
        if (!head || !head->next) return head;
        ListNode *rhead = nullptr;
        while (head) {
            ListNode *ptr = head;
            head = head->next;
            ptr->next = rhead;
            rhead = ptr;
        }
        return rhead;
    }
};
