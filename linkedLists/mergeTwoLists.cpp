#include <iostream>
using namespace std;

typedef struct node {
    int data;
    node *next;
} Node;


Node* reverseList(Node *head)
{
    Node *new_head = nullptr;

    while (head) {
        Node *tmp = head;
        head = head->next;
        tmp->next = new_head;
        new_head = temp;
    }
    return new_head;
}

Node* mergeLists(Node* a, Node* b) 
{
    Node* result = NULL;
 
    if (a == NULL) 
        return b;
    else if (b == NULL) 
        return a;
 
    if (a->data <= b->data) {
        result = a;
        result->next = mergeLists(a->next, b);
    } else {
        result = b;
        result->next = mergeLists(a, b->next);
    }
    return(result);
}

void addItem(Node **head, int item)
{
    Node *tmpnode = new Node;
    tmpnode->data = item;
    tmpnode->next = nullptr;
    if (!(*head)) *head = tmpnode;
    else {
        tmpnode->next = *head;
        *head = tmpnode;
    }
}

void printList(Node* mergeList)
{
    Node *head = mergeList;
    while (head) {
        cout << head->data << ", ";
        head = head->next;
    }
    cout << "\n";
}

int main(void)
{
    Node *L1 = nullptr;
    addItem(&L1, 4);
    addItem(&L1, 3);
    addItem(&L1, 2);
    addItem(&L1, 1);
    cout << "L1 : "; printList(L1);
    Node *L2 = nullptr;
    addItem(&L2, 6);
    addItem(&L2, 5);
    addItem(&L2, 3);
    cout << "L2 : "; printList(L2);
    Node* mergeList = mergeLists(L1, L2);
    cout << "Merged List: "; printList(mergeList);
}
