package binarySearch

import (
	"testing"
)

func TestBinarySearch(t *testing.T) {

	array := []int{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}

	if !BinarySearch(array, 6) {
		t.Errorf("binary search failed to find 6 which is in array\n")
	}

	if BinarySearch(array, 21) {
		t.Errorf("binary search failed - 21 is not in the array\n")
	}

}
