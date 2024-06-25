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
    TreeNode* buildTree(vector<int> preorder, vector<int> inorder)
    {
        if (0 == preorder.size() || 0 == inorder.size()) return nullptr;
        auto i = find(inorder.begin(), inorder.end(), preorder[0]) - inorder.begin();
        TreeNode *root = new TreeNode(preorder[0]);
        root->left = buildTree(vector<int>(preorder.begin()+1, preorder.begin()+1+i),
                               vector<int>(inorder.begin(), inorder.begin()+i));
        root->right = buildTree(vector<int>(preorder.begin()+1+i, preorder.end()),
                               vector<int>(inorder.begin()+i+1, inorder.end()));
        return root;
    }
};
