#include <iostream>

using namespace std;

struct Node {
    int data;
    Node *next;
};

Node* reverseList(Node *head)
{
    Node *new_head = nullptr;
    while (head) {
        Node *tmp = head;
        head = head->next; // moves forward the head.
        tmp->next = new_head;
        new_head = tmp;
    }
    return new_head; // reversed list head.
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
    Node *rhead = reverseList(head);
    printList(rhead);
}
