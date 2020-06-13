'''
Given a non-empty, singly linked list with head
node head, return a middle node of linked list.

If there are two middle nodes, return the
second middle node.
'''

class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None

class Solution(object):
    def middleNote(self, head):
        slow = head
        fast = head
        while fast and fast.next:
            slow = slow.next
            fast = fast.next.next
        return slow

