
/**
 * Merge two sorted linked lists and return it as a new list.
 * The new list should be made by splicing together the nodes
 * of the first two lists.
 *
 * Example:
 * Input: 1->2->4, 1->3->4
 * Output: 1->1->2->3->4->4
 */


#include <iostream>

 struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
 };

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
    {
        ListNode dummy(0);
        ListNode *l3 = &dummy;
        while (l1 && l2) {
            if (l1->val < l2->val) {
                l3->next = l1;
                l3 = l3->next;
                l1 = l1->next;
            } else {
                l3->next = l2;
                l3 = l3->next;
                l2 = l2->next;
            }
        }
        l3->next = l1 ? l1 : l2;
        return dummy.next;
    }
};


int main(void)
{
    Solution s1;
}
