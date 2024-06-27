package stack

import (
	"testing"
)

func TestPush(t *testing.T) {

	s := Init()
	items := []int{11, 3, 9, 2, 1, -20, 23, 5, 29, 7}
	for _, item := range items {
		s.Push(item)
	}

	size := s.Size()
	if size != len(items) {
		t.Errorf("stack size error. expected = %v, returned = %v\n", len(items), size)
	}
}

func TestPop(t *testing.T) {

	s := Init()
	items := []int{11, 3, 9, 2, 1, -20, 23, 5, 29, 7}
	for _, item := range items {
		s.Push(item)
	}

	numOfItems := len(items)
	var i int

	for i = 1; i <= numOfItems; i++ {

		item, err := s.Pop()
		if err != nil {
			t.Errorf("pop failed: %v\n", err)
		}
		if item != items[numOfItems-i] {
			t.Errorf("item mismatch. expected = %v, returned = %v\n", items[numOfItems-i], item)
		}
	}
}

func TestIsEmpty(t *testing.T) {

	s := Init()
	items := []int{11, 3, 9, 2, 1, -20, 23, 5, 29, 7}
	for _, item := range items {
		s.Push(item)
	}

	if s.IsEmpty() {
		t.Errorf("stack should not be empty\n")
	}

	numOfItems := len(items)
	for i := 1; i <= numOfItems; i++ {
		s.Pop()
	}

	if !(s.IsEmpty()) {
		t.Errorf("stack should have been empty\n")
	}
}

func TestPeek(t *testing.T) {

	s := Init()
	items := []int{11, 3, 9, 2, 1, -20, 23, 5, 29, 7}
	for _, item := range items {
		s.Push(item)
	}

	front, err := s.Peek()
	if err != nil {
		t.Errorf("error not expected: %v\n", err)
	}

	if front != items[len(items)-1] {
		t.Errorf("Peek error. expected = %v, returned = %v\n", items[len(items)-1], front)
	}

}

func TestSize(t *testing.T) {

	s := Init()
	items := []int{11, 3, 9, 2, 1, -20, 23, 5, 29, 7}
	for _, item := range items {
		s.Push(item)
	}

	numOfItems := len(items)
	size := s.Size()
	if numOfItems != size {
		t.Errorf("expected size = %v, returned = %v\n", numOfItems, size)
	}
}
