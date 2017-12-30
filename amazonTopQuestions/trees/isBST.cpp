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
    bool isValidBST(TreeNode* root)
    {
        return isBST(root, LONG_MIN, LONG_MAX);
        // return isBSTUtil(root); // inefficient solution.
    }
    
    bool isBST(TreeNode *root, long min, long max)
    {
        if (nullptr == root) return true;
        return root->val > min && root->val < max &&
            isBST(root->left, min, root->val) &&
            isBST(root->right, root->val, max);
    }
    
    int minVal(TreeNode *node)
    {
        TreeNode *p = node;
        while (p->left) node = p->left;
        return p->val;
    }
    int maxVal(TreeNode *node)
    {
        TreeNode *p = node;
        while (p->right) p = p->right;
        return p->val;
    }
    bool isBSTUtil(TreeNode *root)
    {
        if (nullptr == root) return true;
        if (root->left && minVal(root->left) >= root->val) return false;
        if (root->right && maxVal(root->right) <= root->val) return false;
        if (!isBSTUtil(root->left) || !isBSTUtil(root->right)) return false;
        return true;
    }
};
