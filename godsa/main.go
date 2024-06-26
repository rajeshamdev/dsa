package main

import (
	"fmt"

	"github.com/rajeshamdev/dsa/godsa/queue"
	"github.com/rajeshamdev/dsa/godsa/stack"
)

func main() {

	{
		stack := stack.Init()
		fmt.Printf("stack: %v\t %T\n", stack, stack)
		for i := 1; i <= 10; i++ {
			stack.Push(i)
		}

		fmt.Printf("stack: %v\n", stack)

		item, err := stack.Pop()
		fmt.Printf("poped: item : %v, err: %v\n", item, err)

		item, err = stack.Pop()
		fmt.Printf("poped: item : %v, err: %v\n", item, err)

		item, err = stack.Peek()
		fmt.Printf("peek: item : %v, err: %v\n", item, err)

		fmt.Printf("stack: %v\n", stack)
	}

	{
		q := queue.Init()
		fmt.Printf("queue: %v\t %T\n", q, q)
		for i := 1; i <= 10; i++ {
			q.Enqueue(i)
		}

		fmt.Printf("queue: %v\n", q)

		item, err := q.Dequeue()
		fmt.Printf("dequeue: item : %v, err: %v\n", item, err)

		item, err = q.Dequeue()
		fmt.Printf("dequeue: item : %v, err: %v\n", item, err)

		item, err = q.Front()
		fmt.Printf("front: item : %v, err: %v\n", item, err)

		fmt.Printf("queue: %v\n", q)
	}

}
