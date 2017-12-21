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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
    {
        if (!headA || !headB) return nullptr;
        ListNode *pa = headA, *pb = headB;
        while (pa && pb && (pa != pb)) {
            pa = pa->next;
            pb = pb->next;
            if (pa == pb) return pa;
            if (!pa) pa = headB;
            if (!pb) pb = headA;
        }
        return pa;
    }
};
