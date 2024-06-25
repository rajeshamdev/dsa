#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *left;
    Node *right;
};

Node*
createBST(int A[], int left, int right)
{
    if (left > right) return nullptr;
    int mid = (left+right)/2;
    Node *node = new Node;
    node->data = A[mid];
    node->left = createBST(A, left, mid-1);
    node->right = createBST(A, mid+1, right);
    return node;
}

void
inOrder(Node *head)
{
    if (!head) return;
    inOrder(head->left);
    printf("%d ", head->data);
    inOrder(head->right);
}

int
main(void)
{
    int A[] = {1, 2, 3, 4, 5, 6, 7};
    int len = sizeof(A)/sizeof(A[0]);
    Node* root = createBST(A, 0, len-1);
    inOrder(root);
}
