/**
 * Given a linked list, remove the n-th node from the end of
 * list and return its head.

 * Example:
 * Given linked list: 1->2->3->4->5, and n = 2.
 * After removing the second node from the end, the linked
 * list becomes 1->2->3->5.
 *
 * Note:
 * Given n will always be valid.
 * Follow up:
 * Could you do this in one pass?
 */

#include <iostream>

 struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
 };

// This is one pass solution.
// Maintain two pointers - fast and slow.
// 1) move fast pointer onto n+1 th node.
// 2) move both pointers one step at a time till fast pointer reach NULL pointer.
//    This keeps fast and slow pointers n nodes apart.
// 3) delink slow next (which is nth node).
//
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {

        if (head == nullptr || n == 0) return head;

        ListNode dummy(0);
        dummy.next = head;
        ListNode *slow, *fast;
        slow = fast = &dummy;
        auto cnt = 1;

        // move fast pointer onto (n+1) nodes
        while (cnt++ <= n+1) fast = fast->next;

        // keep moving fast and slow pointers till fast pointer
        // reach end. This keeps slow and fast pointers n nodes apart
        while (fast) slow = slow->next, fast = fast->next;

        // delink nth node
        slow->next =  slow->next->next;
        return dummy.next;
    }
};

int
main(void) {
    Solution s1;
}
