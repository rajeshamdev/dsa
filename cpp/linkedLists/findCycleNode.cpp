/*
 * Given a linked list, return the node where the
 * cycle begins. If there is no cycle, return null.
 *
 * To represent a cycle in the given linked list,
 * we use an integer pos which represents the position
 * (0-indexed) in the linked list where tail connects
 * to. If pos is -1, then there is no cycle in the
 * linked list.
 *
 * Note: Do not modify the linked list.
 */


#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x): val(x), next(NULL) {}
};

class Solution {
public:
    ListNode *detectCycle(ListNode *head)
    {
        ListNode *slow = head;
        ListNode *fast = head;
        bool cycle = false;

        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                cycle = true;
                break;
            }
        }

        if (!cycle) return nullptr;

        slow = head;
        while (slow != fast) {
            slow = slow->next;
            fast = fast->next;
        }
        return slow;
    }
};

int
main(void) {
    Solution s1;
}
