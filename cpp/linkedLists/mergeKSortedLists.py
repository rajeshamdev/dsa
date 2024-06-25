"""
 Merge k sorted linked lists and return it as one sorted list.
 Analyze and describe its complexity.

 Example:
 Input:
 [
  1->4->5,
  1->3->4,
  2->6
 ]
 Output: 1->1->2->3->4->4->5->6

 Time complexity - O (NlogK).
  -> Two lists merge takes O(N) time, where N is elements of two lists.
  -> merging two lists repeated logK times, where K is number of lists.

  Space complexity is constant - O(1).
 """
# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next

class Solution(object):
    def mergeKLists(self, lists):
        """
        :type lists: List[ListNode]
        :rtype: ListNode
        """
        llen = len(lists)
        if llen == 0:
            return None
        llen -= 1
        while llen :
            i = 0
            j = llen

            while i < j:
                lists[i] = self.mergeTwoLists(lists[i], lists[j])
                i += 1
                j -= 1
                if i >= j:
                    llen = j
        return lists[0]

    def mergeTwoLists(self, l1, l2):
        head = ListNode(0)
        l3 = head
        while l1 and l2:
            if l1.val < l2.val:
                l3.next = l1
                l1 = l1.next
                l3 = l3.next
            else:
                l3.next = l2
                l2 = l2.next
                l3 = l3.next
        l3.next = l1 if l1 else l2
        return head.next

