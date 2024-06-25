package main

type ListNode struct {
	Val  int
	Next *ListNode
}

func reverseList(head *ListNode) *ListNode {

	var rList *ListNode

	for head != nil {
		p := head
		head = head.Next
		p.Next = rList
		rList = p
	}

	return rList

}

func main() {
}
