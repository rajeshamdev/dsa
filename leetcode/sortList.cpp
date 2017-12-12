#include <bits/stdc++.h>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode* Merge(ListNode *l1, ListNode *l2)
{
    ListNode *result = nullptr;

    if (!l1) return l2;
    else if (!l2) return l1;

    if (l1->val < l2->val) {
        result = l1;
        result->next = Merge(l1->next, l2);
    } else {
        result = l2;
        result->next = Merge(l1, l2->next);
    }
    return result;
}

ListNode* sortList(ListNode *list)
{
    if (!list || !list->next) return list;
    ListNode *slow = list;
    ListNode *fast = list->next;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    fast = slow->next;
    slow->next = nullptr;
    return Merge(list, fast);
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

    //ListNode *sumList = addTwoNumbers(L1, L2);        
    //printList(sumList);
}
