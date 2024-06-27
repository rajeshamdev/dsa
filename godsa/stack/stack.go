package stack

import (
	"errors"
)

type Stack struct {
	items []int
}

func Init() Stack {
	return Stack{}
}

func (s *Stack) Push(item int) {
	s.items = append(s.items, item)
}

func (s *Stack) Pop() (int, error) {

	if len(s.items) == 0 {
		return 0, errors.New("empty stack")
	}

	numOfItems := len(s.items)

	top := s.items[numOfItems-1]
	s.items = s.items[:numOfItems-1]
	return top, nil
}

func (s *Stack) IsEmpty() bool {
	return len(s.items) == 0
}

func (s *Stack) Peek() (int, error) {

	if len(s.items) == 0 {
		return 0, errors.New("stack is empty")
	}

	return s.items[len(s.items)-1], nil
}

func (s *Stack) Size() int {
	return len(s.items)
}
