package binarySearch

func BinarySearch(array []int, key int) bool {

	low, high := 0, len(array)-1

	for low <= high {

		mid := low + (high-low)/2

		if key == array[mid] {
			return true
		} else if key < array[mid] {
			// search in the left half
			high = mid - 1
		} else {
			// search in the right half
			low = mid + 1
		}
	}
	return false
}
