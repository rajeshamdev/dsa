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
        stack<TreeNode*> q;
        vector<int> inorder;
        TreeNode *pCur = root;
        while (!q.empty() || pCur) {
            if (pCur) {
                q.push(pCur);
                pCur = pCur->left;
            } else {
                TreeNode *pNode = q.top();
                inorder.push_back(pNode->val);
                q.pop();
                pCur = pNode->right;
            }
        }
        return inorder;
    }
};
