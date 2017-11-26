#include <iostream>

using namespace std;

struct Node {
    int data;
    Node *next;
};

Node* reverseKNodes(Node **head, int k, Node **last)
{
    Node *new_head = nullptr;
    int count = 0;

    if (*head) {
        *last = *head;
    } else {
        *last = nullptr;
    }

    while (*head && k--) {
        Node *tmp = *head;
        *head = (*head)->next;
        tmp->next = new_head;
        new_head = tmp;
    }
    if (*last)
        (*last)->next = nullptr;
    return new_head;
}

Node* reverseList(Node **head, int k)
{
    Node *last = nullptr;
    Node *rhead = reverseKNodes(head, k, &last);
    Node *tmp = last;;
    while (*head) {
        tmp->next = reverseKNodes(head, k, &last);
        tmp = last;
    }
    return rhead;
}

void push(Node **head, int data)
{
    Node *tmp = new Node;
    tmp->data = data;
    tmp->next = *head;
    *head = tmp;
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
        push(&head, i);
        --i;
    }
    printList(head);
    Node *rhead = reverseList(&head, 3);
    printList(rhead);
}
