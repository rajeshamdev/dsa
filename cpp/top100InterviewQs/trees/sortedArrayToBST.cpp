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
    TreeNode* sortedArrayToBST(vector<int> &vec)
    {
        if (vec.size() == 0) return nullptr;
        if (vec.size() == 1) return new TreeNode(vec[0]);
        
        int mid = vec.size()/2;
        TreeNode *root = new TreeNode(vec[mid]);
        vector<int> left(vec.begin(), vec.begin()+mid);
        vector<int> right(vec.begin()+mid+1, vec.end());
        root->left = sortedArrayToBST(left);
        root->right = sortedArrayToBST(right);
        return root;
        
    }
};
