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
    vector<vector<int>> levelOrder(TreeNode* root)
    {
        if (nullptr == root) return {};
        vector<vector<int>> ans;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            auto size = q.size();
            vector<int> row;
            while (size--) {
                TreeNode *pNode = q.front();
                row.push_back(pNode->val);
                q.pop();
                if (pNode->left) q.push(pNode->left);
                if (pNode->right) q.push(pNode->right);
            }
            ans.push_back(row);
        }
        return ans;
    }
};
