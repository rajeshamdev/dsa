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

void bfs(Node *head)
{
    if (!head) return;
    cout << "Level order traversal of Tree: ";
    queue<Node*> tq;
    tq.push(head);
    while (!tq.empty()) {
        Node *tmp = tq.front();
        cout << tmp->data << ", ";
        tq.pop();
        if (tmp->left)
            tq.push(tmp->left);
        if (tmp->right)
            tq.push(tmp->right);
    }
    cout << "\n";
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
    bfs(root);
}
