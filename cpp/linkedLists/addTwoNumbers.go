package main

/**
 * You are given two non-empty linked lists representing two
 * non-negative integers. The digits are stored in reverse
 * order and each of their nodes contain a single digit.
 * Add the two numbers and return it as a linked list.

* You may assume the two numbers do not contain any leading
* zero, except the number 0 itself.

* Example:
* Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
* Output: 7 -> 0 -> 8
* Explanation: 342 + 465 = 807.
**/

type ListNode struct {
	Val  int
	Next *ListNode
}

func addTwoNumbers(l1 *ListNode, l2 *ListNode) *ListNode {

	dummy := ListNode{}
	l3 := &dummy
	carry := 0

	for l1 != nil || l2 != nil || carry != 0 {

		if l1 != nil {
			carry += l1.Val
			l1 = l1.Next
		}

		if l2 != nil {
			carry += l2.Val
			l2 = l2.Next
		}

		l3.Next = &ListNode{Val: carry % 10}
		l3 = l3.Next
		carry /= 10
	}

	return dummy.Next
}

func main() {
}
