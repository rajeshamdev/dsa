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
        unordered_map<RandomListNode*, RandomListNode*> nodeMap;
        RandomListNode *pCur = head;
        while (pCur) {
            RandomListNode *nNode = new (nothrow) RandomListNode(pCur->label);
            if (nullptr == nNode) return nullptr;
            nodeMap.emplace(pCur, nNode);
            // nodeMap.emplace(pCur, new RandomListNode(pCur->label));
            pCur = pCur->next;
        }
        pCur = head;
        RandomListNode *clone;
        while (pCur) {
            clone = nodeMap[pCur];
            clone->next = nodeMap[pCur->next];
            clone->random = nodeMap[pCur->random];
            pCur = pCur->next;
        }
        return nodeMap[head];
    }
};
