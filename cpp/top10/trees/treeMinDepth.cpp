#include <bits/stdc++.h>

/**
 * Minimum depth of tree is the number of nodes in the
 * shortest path from root to a leaf node.
 */

using namespace std;

struct Node {
    int data;
    Node *left, *right;
};

/* This is O(N) as it will traverse all the nodes of tree. */
int minDepth1(Node *head)
{
    if (head == nullptr) return 0;
    else
        return (1+std::min(minDepth1(head->left), minDepth1(head->right)));
}

/**
 * A better approach would be level order traversal.
 * During the level order traversal if there is a leaf
 * node (whose left and righ sub-tree is nullptr), then,
 * depth upto that node is min depth of the tree.
 */

int minDepth2(Node *head)
{
    if (head == nullptr) return 0;

    queue<pair<Node*, int>> q;
    q.push({head, 1});
    while (!q.empty()) {
        Node *temp = q.front().first;
        int depth = q.front().second;
        q.pop();
        if (temp->left == nullptr && temp->right == nullptr) {
            return depth;
        }
        if (temp->left) {
            q.push({temp->left, depth+1});
        }
        if (temp->right) {
            q.push({temp->right, depth+1});
        }
    }
}

Node* createNode(int data)
{
    Node *temp = new Node;
    temp->data = data;
    temp->left = temp->right = nullptr;
    return temp;
}

int main(void)
{
    Node *root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    cout << "mindepth approach-1 = " << minDepth1(root) << "\n";
    cout << "mindepth approach-2 = " << minDepth2(root) << "\n";
    return 0;
}
