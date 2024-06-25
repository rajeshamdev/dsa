
/*
 * Fix loop in linked list Floyd's loop detection algorithm.
 */

#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    void fixLoop(ListNode *head)
    {
        ListNode *slow, *fast;
        slow = fast = head;

        auto loop= false;
        // Step-1: Foyds Algorithm - detect loop.
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                loop = true;
                break;
            }
        }

        // no loop
        if (!loop) return;

        // step-2: find the node where cycle is.
        slow = head;
        while (slow != fast){
            slow = slow->next;
            fast = fast->next;
        }

        // step-3: remove the loop.
        while (slow->next != fast) {
            slow = slow->next;
        }
        slow->next = nullptr;
    }
};

int
main(void) {
    Solution s1;
}
