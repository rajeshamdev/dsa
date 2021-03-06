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
    ListNode* oddEvenList(ListNode* head)
    {
        if (nullptr == head) return head;
        ListNode *odd = head, *even = head->next, *evenhead = even;
        while (even && even->next) {
            odd = odd->next = odd->next->next;
            even = even->next = even->next->next;
        }
        odd->next = evenhead;
        return head;
    }
};
