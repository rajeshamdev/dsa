class ListNode(object):
    def __init__(self, x):
        self.val = x
        self.next = None

class Solution(object):
    def reverseList(self, head):
        rList = None
        while head:
            tmp = head
            head = head.next
            tmp.next = rList
            rList = tmp
        return rList
