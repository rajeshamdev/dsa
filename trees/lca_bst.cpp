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

Node* lca(Node *root, int n1, int n2)
{
    if (root == nullptr)
        return root;

    if (n1 < root->data && n2 < root->data)
        return lca(root->left, n1, n2);
    if (n1 > root->data && n2 > root->data)
        return lca(root->right, n1, n2);
    return root;
}

int main(void)
{
    Node *root = addNode(20);
    root->left = addNode(8);
    root->right = addNode(22);
    root->left->left = addNode(4);
    root->left->right = addNode(12);
    root->left->right->left  = addNode(10);
    root->left->right->right = addNode(14);

    Node *node = lca(root, 10, 14);
    cout << node->data << "\n";
}
