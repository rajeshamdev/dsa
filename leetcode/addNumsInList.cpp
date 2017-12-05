#include <bits/stdc++.h>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
{
    int carry = 0;
    ListNode *sumList = new ListNode(0);
    ListNode *cur = sumList;

    while (l1 || l2) {
        int x = l1 ? l1->val : 0;
        int y = l2 ? l2->val : 0;
        int sum = x + y + carry;
        carry = sum/10;
        cur->next = new ListNode(sum%10);
        cur = cur->next;
        if (l1) l1 = l1->next;
        if (l2) l2 = l2->next;
    }
    if (carry) {
        cur->next = new ListNode(carry);
        cur = cur->next;
    }
    return sumList->next;
}

void push(ListNode *& L, int data)
{
    ListNode *tmp = new ListNode(data);
    tmp->next = L;
    L = tmp;
}

void printList (const ListNode *L)
{
    while (L) {
        cout << L->val;
        L = L->next;
        if (L) cout << "->";
    }
    cout << "\n";
}

int main(void)
{
    ListNode *L1 = nullptr;
    ListNode *L2 = nullptr;
    push(L1, 9);
    push(L1, 7);
    push(L1, 6);
    printList(L1);

    push(L2, 4);
    push(L2, 9);
    push(L2, 9);
    printList(L2);

    ListNode *sumList = addTwoNumbers(L1, L2);        
    printList(sumList);
}
