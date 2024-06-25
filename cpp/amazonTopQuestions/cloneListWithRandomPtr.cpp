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
        RandomListNode *cur = head;
        // Step1: clone nodes between each node.
        while (cur) {
            RandomListNode *ptr = cur->next;
            cur->next = new RandomListNode(cur->label);
            cur->next->next = ptr;
            cur = ptr;
        }
        // Step2: adjust random pointers.
        cur = head;
        while (cur) {
            cur->next->random = cur->random ? cur->random->next : nullptr;
            cur = cur->next->next;
        }
        // Step3: delink - restores the lists.
        RandomListNode *orig = head, *clone = head->next, *res = head->next;
        while (clone) {
            orig = orig->next = orig->next->next;
            clone = clone->next = clone->next ? clone->next->next : nullptr;
        }
        return res;
    }
};
