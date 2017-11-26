#include <iostream>

using namespace std;

struct Node {
    int data;
    Node *next;
};

/**
 * This is simple reverse of linked list.  It takes reference
 * of list head pointer and return a reverse list of size <= k.
 * It cuts off the reversed list from the head pointer.
 */
Node* reverseKNodes(Node *&head, int k)
{
    Node *new_head = nullptr;
    while (head && k--) {
        Node *tmp = head;
        head = head->next; // moves forward the head.
        tmp->next = new_head;
        new_head = tmp;
    }
    return new_head; // reversed list head.
}

/**
 * This is bit tricky (and confusing).
 * The core idea is: we need to save the head pointer before
 * reversing K elements of the list. And link its 'next' pointer
 * with the reversed list head.
 * 
 */
Node* reverseList(Node *&head, int k)
{
    Node *prevHead = head;
    Node *rhead = reverseKNodes(head, k); // store the head of whole list.
    while (head) {
        Node *tmp = head;
        prevHead->next = reverseKNodes(head, k);
        prevHead = tmp;
    }
    return rhead;
}

void push(Node *&head, int data)
{
    Node *tmp = new Node;
    tmp->data = data;
    tmp->next = head;
    head = tmp;
}

void printList(Node *head)
{
    Node *tmp = head;
    while (tmp) {
        cout << tmp->data << ", ";
        tmp = tmp->next;
    }
    cout << "\n";
}
int main(void)
{
    Node *head = nullptr;
    int i = 10;
    while (i) {
        push(head, i);
        --i;
    }
    printList(head);
    Node *rhead = reverseList(head, 4);
    printList(rhead);
}
