package queue

import (
	"testing"
)

func TestEnqueue(t *testing.T) {

	q := Init()
	for i := 1; i <= 10; i++ {
		q.Enqueue(i)
	}

	size := q.Size()
	if size != 10 {
		t.Errorf("Expected items in queue to be 10, but found: %v\n", size)
	}
}

func TestDequeue(t *testing.T) {

	q := Init()
	items := []int{2, 3, 11, 5, 9, 7, 10, 21, 25, 1}
	for _, item := range items {
		q.Enqueue(item)
	}

	for _, item := range items {
		num, err := q.Dequeue()
		if err != nil {
			t.Errorf("dequeue should not have returned : %v\n", err)
		}
		if num != item {
			t.Errorf("dequeue: expected = %v, returned = %v\n", item, num)
		}
	}

}

func TestIsEmpty(t *testing.T) {
	q := Init()

	if !q.IsEmpty() {
		t.Error("queue is expected to be empty")
	}

	items := []int{2, 3, 11, 5, 9, 7, 10, 21, 25, 1}
	for _, item := range items {
		q.Enqueue(item)
	}

	if q.IsEmpty() {
		t.Error("queue expected not to be empty\n")
	}

	// dequeue all items
	for i := 1; i <= len(items); i++ {
		q.Dequeue()
	}

	if !q.IsEmpty() {
		t.Error("queue is expected to be empty")
	}
}
