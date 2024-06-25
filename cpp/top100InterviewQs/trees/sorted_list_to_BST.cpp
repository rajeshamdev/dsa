/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head)
    {
        if (nullptr == head) return nullptr;
        if (nullptr == head->next) {
            return new TreeNode(head->val);
        }
        ListNode *s = head, *f = head, *prev = nullptr;
        while (f && f->next) {
            prev = s;
            s = s->next, f = f->next->next;
        }
        prev->next = nullptr;
        TreeNode *root = new TreeNode(s->val);
        root->left = sortedListToBST(head);
        root->right = sortedListToBST(s->next);
        return root;
    }
};
