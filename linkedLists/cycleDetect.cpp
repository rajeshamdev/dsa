#include <iostream>

typedef struct Node {
    int data;
    Node *next;
} Node;

bool deleteLoop(Node *head)
{
    if (!head) return false;

    Node *slow = head;
    Node *fast = head;

    bool loop = false;

    // One node and its a loop.
    if (slow == slow->next) {
        loop = true;
    }
    // Step-1: Detect the loop using Floyd cycle detection algorith.
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (fast == slow) {
            // loop detected.
            loop == true;
            break;
        }
    }
    if (loop == false) return false;

    // Step-2: Find the start of the loop.
    slow = head;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }

    // Step-3: Start from the loop node and clear the loop.
    while (slow->next != fast) {
        slow = slow->next;
    }
    slow->next = nullptr;
}
