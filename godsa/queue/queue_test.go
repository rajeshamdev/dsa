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
	if !(q.IsEmpty()) {
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

	if !(q.IsEmpty()) {
		t.Error("queue is expected to be empty")
	}
}

func TestFront(t *testing.T) {

	q := Init()
	if _, err := q.Front(); err == nil {
		t.Error("this should have been error as there is nothing in queue\n")
	}

	items := []int{2, 3, 11, 5, 9, 7, 10, 21, 25, 1}
	for _, item := range items {
		q.Enqueue(item)
	}

	item, err := q.Front()
	if err != nil {
		t.Errorf("Front returned: %v\n", err)
	}
	if item != items[0] {
		t.Errorf("Front error. expected = %v, returned = %v\n", items[0], item)
	}

	// dequeue all items
	for i := 1; i <= len(items); i++ {
		q.Dequeue()
	}

	if _, err = q.Front(); err == nil {
		t.Error("this should have been error as there is nothing in queue\n")
	}
}

func TestSize(t *testing.T) {

	q := Init()
	items := []int{2, 3, 11, 5, 9, 7, 10, 21, 25, 1}
	for _, item := range items {
		q.Enqueue(item)
	}

	size := q.Size()
	if size != len(items) {
		t.Errorf("queue size expected = %v, actual = %v\n", len(items), size)
	}
}
