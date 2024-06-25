#include <bits/stdc++.h>

using namespace std;
struct Node {
    int data;
    Node *next;
};

void push(Node *&head, int data)
{
    Node *tmp = new Node;
    tmp->data = data;
    tmp->next = head;
    head = tmp;
}

void printList(Node *head)
{
    while (head) {
        cout << head->data << ", ";
        head = head->next; 
    }
    cout << "\n";
}

void unionFind(Node *list1, Node *list2)
{
    unordered_set<int> unionSet;
    while (list1) {
        unionSet.insert(list1->data);
        list1 = list1->next;
    }
    while (list2) {
        if (unionSet.find(list2->data) == unionSet.end()) {
            unionSet.insert(list2->data);
        }
        list2 = list2->next;
    }
    cout << "Union of List1 and List2 : ";
    for (int i : unionSet) {
        cout << i << ", ";
    }
    cout << "\n";
}

void intersectionFind(Node *list1, Node *list2)
{
    unordered_set<int> iSet;
    while (list1) {
        iSet.insert(list1->data);
        list1 = list1->next;
    }
    vector<int> ivec;
    while (list2) {
        if (iSet.find(list2->data) != iSet.end()) {
            ivec.push_back(list2->data);
        }
        list2 = list2->next;
    }
    cout << "Intersection of List1 and List2 : ";
    for (int i : ivec) {
        cout << i << ", ";
    }
    cout << "\n";
}

int main(void)
{
    Node *list1 = nullptr;
    push(list1, 1);
    push(list1, 2);
    push(list1, 3);
    push(list1, 4);
    push(list1, 5);
    cout << "List1 : ";
    printList(list1);

    Node *list2 = nullptr;
    push(list2, 5);
    push(list2, 4);
    push(list2, 3);
    push(list2, 25);
    cout << "List2 : ";
    printList(list2);
    unionFind(list1, list2);
    intersectionFind(list1, list2);
}
