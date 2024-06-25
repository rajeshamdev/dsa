#include <bits/stdc++.h>

using namespace std;

struct Node {
    int data;
    Node *left, *right;
};

int maxPathSum(Node *head)
{
    if (head == nullptr) return 0;

    queue<Node*> q;
    int maxPathSum = head->data;
    q.push(head);
    while (!q.empty()) {
        Node *temp = q.front();
        q.pop();
        if (temp->left && (temp->left->data + temp->data > temp->data)) {
            q.push(temp->left);
            maxPathSum += temp->left->data;
        }
        if (temp->right && (temp->right->data + temp->data > temp->data)) {
            q.push(temp->right);
            maxPathSum += temp->right->data;
        }
    }
    return maxPathSum;
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
    Node *root = createNode(10);
    root->left        = createNode(2);
    root->right       = createNode(10);
    root->left->left  = createNode(20);
    root->left->right = createNode(1);
    root->right->right = createNode(-25);
    root->right->right->left   = createNode(3);
    root->right->right->right  = createNode(4);

    cout << "maxpathSum = " << maxPathSum(root) << "\n";
    return 0;
}
