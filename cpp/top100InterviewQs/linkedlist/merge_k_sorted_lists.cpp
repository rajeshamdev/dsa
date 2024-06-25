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
    
    ListNode* mergeSortedLists(ListNode *l1, ListNode *l2)
    {
        if (nullptr == l1) return l2;
        if (nullptr == l2) return l1;
        ListNode dummy(0);
        ListNode *p = &dummy;
        while (l1 && l2) {
            if (l1->val < l2->val) {
                p->next = l1;
                l1 = l1->next;
            } else {
                p->next = l2;
                l2 = l2->next;
            }
            p = p->next;
        }
        p->next = l1 ? l1 : l2;
        return dummy.next;
    }
    
    ListNode* mergeKLists(vector<ListNode*>& lists)
    {
        auto len = lists.size();
        if (0 == len--) return {};
        while (len) {
            auto i = 0;
            auto j = len;
            while (i < j) {
                lists[i] = mergeSortedLists(lists[i], lists[j]);
                i++, j--;
                if (i>=j)  len = j;
            }
        }
        return lists[0];
    }
};
