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
    ListNode* mergeTwoSortedLists(ListNode *l1, ListNode *l2)
    {
        ListNode dummy(0);
        ListNode *l3 = &dummy;
        while (l1 && l2) {
            if (l1->val < l2->val)
                l3 = l3->next = l1, l1 = l1->next;
            else l3 = l3->next = l2, l2 = l2->next;
        }
        l3->next = l1 ? l1 : l2;
        return dummy.next;
    }
    
    
    ListNode* mergeKLists(vector<ListNode*>& lists)
    {
        auto len = lists.size();
        if (0 == len--) return {};
        while(len) {
            auto i = 0;
            auto j = len;
            while (i < j) {
                lists[i] = mergeTwoSortedLists(lists[i], lists[j]);
                i++, j--;
                if (i >= j) len = j;
            }
        }
        return lists[0];
    }
};
