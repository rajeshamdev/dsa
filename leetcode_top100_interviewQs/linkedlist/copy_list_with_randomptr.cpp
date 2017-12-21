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
        // Create nodes in between each node.
        while (cur) {
            RandomListNode *p2 = cur->next;
            cur->next = new RandomListNode(cur->label);
            cur->next->next = p2;
            cur = p2;    
        }
        
        cur = head;
        // adjust random pointers
        while (cur) {
            cur->next->random = cur->random ? cur->random->next : nullptr;
            cur = cur->next->next;
        }
        
        RandomListNode *orig = head, *clone = head->next;
        RandomListNode *temp = clone;
        while (orig && clone) {
            orig->next = orig->next ? orig->next->next : orig->next;
            orig = orig->next;
            clone->next = clone->next ? clone->next->next : clone->next;
            clone = clone->next;
        }
        return temp;
    }
};
