
/**
 * Merge k sorted linked lists and return it as one sorted list.
 * Analyze and describe its complexity.
 *
 * Example:
 * Input:
 * [
 *  1->4->5,
 *  1->3->4,
 *  2->6
 * ]
 * Output: 1->1->2->3->4->4->5->6
 *
 * Time complexity - O (NlogK).
 *  -> Two lists merge takes O(N) time, where N is elements of two lists.
 *  -> merging two lists repeated logK times, where K is number of lists.
 *
 *  Space complexity is constant - O(1).
 */
#include <iostream>
#include <vector>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* mergeKLists(std::vector<ListNode*>& lists) {
        auto len = lists.size();
        if (len == 0) return nullptr;
        --len;
        while(len) {
            auto i = 0;
            auto j = len;
            while (i < j) {
                lists[i] = mergeTwoSortedLists(lists[i], lists[j]);
                i++;
                j--;
                if (i >= j) len = j;
            }
        }
    return lists[0];
    }

    ListNode* mergeTwoSortedLists(ListNode *l1, ListNode *l2) {
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

int
main(void) {
    Solution s1;
}
