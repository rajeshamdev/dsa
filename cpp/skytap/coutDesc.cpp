#include <iostream>
#include <vector>
#include <queue>

using namespace std;
class Node {
    public:
        Node *left;
        Node *right;
        Node(void) : left(nullptr), right(nullptr) {}
};
// Do simple depth first traversal and count all nodes underneath
// a given node. Nodes are pushed to / popped from "queue" data
// structures while traversing.
int count_descendants(Node *node)
{
    if (node == nullptr) return 0;
    int cnt = 0;
    queue<Node*> q;
    q.push(node);
    while (!q.empty()) {
        Node *tmp = q.front();
        q.pop();
        if (tmp->left) {
            q.push(tmp->left);
            ++cnt;
        }
        if (tmp->right) {
            q.push(tmp->right);
            ++cnt;
        }
    }
    return cnt;
}
