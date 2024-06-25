/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution
{ 
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
    {
        ListNode dummy(0);
        ListNode *p = &dummy;
        auto sumNRem = 0;
        while (l1 || l2 || sumNRem) {
            if (l1) sumNRem += l1->val, l1 = l1->next;
            if (l2) sumNRem += l2->val, l2 = l2->next;
            p = (p->next = new ListNode(sumNRem%10));
            //p = p->next;
            sumNRem /= 10;
        }
        return dummy.next;
    }
};
