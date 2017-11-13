
/* Reference: http://cslibrary.stanford.edu/110/BinaryTrees.pdf */


/* In BST, minimum value is in the left most node. */
int minValue(struct node *head)
{
    if (!head) return 0;
    
    while (head->next) head = head->next;
    
    return head->data;
}

/* *
 * Given a BST and a sum, return true if the tree has a root-to-leaf path such that adding
 * up all the values along the path equals the given sum. Return false if no such path can
 * be found.
 */
bool hasPathSum(struct node *head, int sum)
{
    if (!head) return sum == 0;
    else {
        int subSum = sum - head->data;
        return hasPathSum(head->left, subSum) || hasPathSum(head->right, subSum);
    }
}

/* Change a tree so that the roles of the left and right pointers are swapped at every node. */
void mirrorTree(struct node *head)
{
    if (!head) return;
    else {
        mirrorTree(head->left);
        mirrorTree(head->right);
        struct node *tmp = head->left;
        head->left = head->right;
        head->right = tmp;
    }
}

/**
 * Given two binary trees, return true if they are structurally identical -- they are made
 * of nodes with the same values arranged in the same way.
 */

bool sameTree(struct node *T1, struct node *T2)
{
    if (!T1 && !T2) return true;
    else if (T1 && T2) {
        return (T->data == T2->data && sameTree(T1->left, T2->left)
                && sameTree(T1->right, T2->right));
    } else return false;
}

/* Given a binary tree, return true of its BST */

bool isBST(struct node *node)
{
    if (!node) return true;
    if (node->left && minVal(node->left) > node->data) return false;
    if (node->right && maxVal(node->right) < node->data) return false;
    if (!isBST(node->left) || !isBST(node->right)) rerturn false;
    return true;
}
