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
    bool isPalindrome(ListNode* head)
    {
        if (nullptr == head || nullptr == head->next) return true;
        ListNode *s, *f;
        s = f = head;
        while (f->next && f->next->next) {
            s = s->next;
            f = f->next->next;
        }
        s->next = reverse(s->next);
        s = s->next;
        while (s) {
            if (s->val != head->val) return false;
            s = s->next;
            head = head->next;
        }
        return true;
    }
    
    ListNode *reverse(ListNode *head)
    {
        if (nullptr == head) return head;
        ListNode *rhead = nullptr;
        while (head) {
            ListNode *p = head;
            head = head->next;
            p->next = rhead;
            rhead = p;
        }
        return rhead;
    }
};
