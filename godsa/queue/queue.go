package queue

import (
	"errors"
)

type Queue struct {
	items []int
}

func Init() Queue {
	return Queue{}
}

func (q *Queue) Enqueue(item int) {
	q.items = append(q.items, item)

}

func (q *Queue) Dequeue() (int, error) {
	if len(q.items) == 0 {
		return 0, errors.New("queue is empty")
	}

	item := q.items[0]
	q.items = q.items[1:]
	return item, nil
}

func (q *Queue) IsEmpty() bool {
	if len(q.items) == 0 {
		return true
	}
	return false
}

func (q *Queue) Front() (int, error) {

	if len(q.items) == 0 {
		return 0, errors.New("queue is empty")
	}

	return q.items[0], nil

}
