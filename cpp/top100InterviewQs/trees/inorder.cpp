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
    vector<int> inorderTraversal(TreeNode* root)
    {
        if (nullptr == root) return {};
        stack<TreeNode*> s;
        vector<int> ans;
        TreeNode *cur = root;
        while (!s.empty() || cur) {
            if (cur) {
                s.push(cur);
                cur = cur->left;
            } else {
                 cur = s.top();
                 ans.push_back(cur->val);
                 s.pop();
                 cur = cur->right;
            }
        }
        return ans;
    }
};
