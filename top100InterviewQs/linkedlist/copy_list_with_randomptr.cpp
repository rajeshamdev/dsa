/**
 * Definition for singly-linked list with a random pointer.
 * struct RandomListNode {
 *     int label;
 *     RandomListNode *next, *random;
 *     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
 * };
 */
class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head)
    {
        if (nullptr == head) return head;
        // Step-1: Insert clone nodes in between each node.
        RandomListNode *cur = head;
        while (cur) {
            RandomListNode *p = cur->next;
            cur->next = new RandomListNode(cur->label);
            cur->next->next = p;
            cur = p;
        }
        // Step-2: Adjust random pointers.
        cur = head;
        while (cur) {
            cur->next->random = cur->random ? cur->random->next: nullptr;
            cur = cur->next->next;
        }
        // Step-3: delink orig and clone
        RandomListNode *orig = head, *clone = head->next;
        RandomListNode *res = clone; // store head of clone to return.
        while (clone) { // no need to check orig pointer here as it trailes clone pointer
            orig = orig->next  = orig->next->next;
            clone = clone->next = clone->next ? clone->next->next : nullptr;
        }
        return res;
    }
};
