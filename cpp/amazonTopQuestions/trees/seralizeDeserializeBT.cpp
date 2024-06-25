/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root)
    {
        ostringstream ostr;
        serialize(root, ostr);
        return ostr.str();
    }
    
    // fold the tree into string using pre-order traversal.
    void serialize(TreeNode *root, ostringstream &ostr)
    {
        if (nullptr == root) {
            ostr << "# ";
            return;
        }
        ostr << root->val << " ";
        serialize(root->left, ostr);
        serialize(root->right, ostr);
    }
    
    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data)
    {
        istringstream istr(data);
        TreeNode *root = deserialize(istr);
        return root;
    }
    TreeNode* deserialize(istringstream &istr)
    {
        string val;
        istr >> val;
        if (val == "#") {
            return nullptr;
        }
        TreeNode *root = new TreeNode(stoi(val));
        root->left = deserialize(istr);
        root->right = deserialize(istr);
        return root;
    }
};
