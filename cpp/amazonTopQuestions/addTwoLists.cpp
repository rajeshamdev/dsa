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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
    {
        ListNode dummy(0); 
        ListNode *l3 = &dummy;
        auto sumAndCarry = 0;
        while (l1 || l2 || sumAndCarry) {
            if (l1) sumAndCarry += l1->val, l1 = l1->next;
            if (l2) sumAndCarry += l2->val, l2 = l2->next;
            l3 = l3->next = new ListNode(sumAndCarry % 10);
            sumAndCarry /= 10;
        }
        return dummy.next;
    }
};
