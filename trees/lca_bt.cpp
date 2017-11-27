#include <bits/stdc++.h>

using namespace std;

struct Node {
    int data;
    Node *left;
    Node *right;
};

Node* addNode(int data)
{
    Node *tmp = new Node;
    tmp->data = data;
    tmp->left = nullptr;
    tmp->right = nullptr;
    return tmp;
}

Node* lca(Node *root, int p, int q)
{
    if (root == nullptr || root->data == p || root->data == q)
        return root;

    Node *left = lca(root->left, p, q);
    Node *right = lca(root->right, p, q);
    if (left && right) return root;
    else if (!left && right ) return right;
    else return left;
}

int main(void)
{
    Node *root = addNode(1);
    root->left = addNode(2);
    root->right = addNode(3);
    root->left->left = addNode(4);
    root->left->right = addNode(5);
    root->right->left = addNode(6);
    root->right->right = addNode(7);

    root->left->left->left = addNode(0);
    root->left->left->right = addNode(9);

    Node *node = lca(root, 9, 5);
    cout << node->data << "\n";
}
