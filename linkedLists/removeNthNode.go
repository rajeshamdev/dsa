package main

// This is one pass solution.
// Maintain two pointers - fast and slow.
// 1) move fast pointer onto n+1 th node.
// 2) move both pointers one step at a time till fast pointer reach NULL pointer.
//    This keeps fast and slow pointers n nodes apart.
// 3) delink slow next (which is nth node).
//

type ListNode struct {
	Val  int
	Next ListNode
}

func removeNthFromEnd(head *ListNode, n int) *ListNode {

	dummy := ListNode{}
	dummy.Next = head
	slow := &dummy
	fast := &dummy
	cnt := 1

	for cnt <= n+1 {
		fast = fast.Next
		cnt++
	}

	for fast != nil {
		slow = slow.Next
		fast = fast.Next
	}

	slow.Next = slow.Next.Next

	return dummy.Next

}

func main() {
}
