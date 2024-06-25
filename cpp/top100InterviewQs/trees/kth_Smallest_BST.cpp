/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution
{
public:
    
    void inorder(TreeNode* root, int &k, int &res)
    {
        if (nullptr == root) return;
        inorder(root->left, k, res);
        --k;
        if (0 == k) {
            res = root->val;
            return;
        }
        inorder(root->right, k, res);
    }

    int kthSmallest(TreeNode* root, int &k)
    {
        int res = 0;
        inorder(root, k, res);
        return res;
    }
    
};
