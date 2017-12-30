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
        ListNode *s = head, *f = head, *r = nullptr;
        while (f && f->next) {
            ListNode *p = s;
            s = s->next;
            f = f->next->next;
            p->next = r;
            r = p;
        }
        if (f) s = s->next;
        while (r && r->val == s->val) {
            r = r->next, s = s->next;
        }
        return r == nullptr;
    }

    bool isPalindrome1(ListNode* head)
    {
        if (nullptr == head || nullptr == head->next) return true;
        ListNode *s = head, *f = head;
        while (f->next && f->next->next) {
            s = s->next, f = f->next->next;
        }
        s->next = reverse(s->next);
        s = s->next;
        while (s && head->val == s->val) {
            head = head->next, s = s->next;
        }
        return s == nullptr;
    }
    ListNode* reverse(ListNode *head)
    {
        ListNode *r = nullptr;
        while (head) {
            ListNode *p = head;
            head = head->next;
            p->next = r;
            r = p;
        }
        return r;
    }
};
