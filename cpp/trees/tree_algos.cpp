#include <iostream>

struct node {
    int data;
    struct node *left;
    struct node *right;
};

struct node*
CreateNewNode(int data)
{   
    struct node *newNode = new node;
    newNode->data = data;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

struct node*
insert(struct node* head, int val)
{   
    if (!head) return CreateNewNode(val);
    
    if (val <= head->data) head->left = insert(head->left, val);
    else head->right = insert(head->right, val);
    return head;
}

// Inorder traversal: print left sub-tree, parent, right sub-tree.
// Inorder traversal prints the ascending sorted order of data.
void
inOrderTraversal(struct node* head)
{   
    if (!head) return;
    inOrderTraversal(head->left);
    printf ("%d ", head->data);
    inOrderTraversal(head->right);
}


// left, right, parent.
void postOderTraversal(struct node* head)
{   
    if (!head) return;
    postOderTraversal(head->left);
    postOderTraversal(head->right);
    printf("%d ", head->data);
}

// parent, left, right.
void preOrderTraversal(struct node* head)
{   
    if (!head) return;
    printf("%d ", head->data);
    preOrderTraversal(head->left);
    preOrderTraversal(head->right);
}

int countNodes(struct node* head)
{   
    if (!head) return 0;
    else return (countNodes(head->left) + 1 + countNodes(head->right));
}

int
height(struct node* head)
{
    if (!head) return -1;
    return (1+std::max(height(head->left), height(head->right)));
}

int
maxDepth(struct node* head)
{
    if (!head) return 0;
    return (1+std::max(maxDepth(head->left), maxDepth(head->right)));
}

int
minDepth(struct node* head)
{
    if (!head) return 0;
    return (1 + std::min(minDepth(head->left), minDepth(head->right)));
}

bool
isBalance(struct node *head)
{
    return (maxDepth(head) - minDepth(head) <= 1);
}

int
main(void)
{
    struct node *root = nullptr;
    root = insert(root, 3);
    root = insert(root, 5);
    root = insert(root, 1);
    inOrderTraversal(root);
    printf("\n");
    printf("Number of nodes in the tree are: %d\n", countNodes(root));
    printf("Tree height: %d\n", maxDepth(root));
}
