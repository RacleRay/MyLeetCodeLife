# import threading


# threading.active_count()
def QuickSort(arr):
	if len(arr) <= 1:
		return arr
	pivot = arr[len(arr) // 2]
	left = [x for x in arr if x < pivot]
	middle = [x for x in arr if x == pivot]
	right = [x for x in arr if x > pivot]
	return QuickSort(left) + middle + QuickSort(right)

if __name__ == '__main__':

	print(QuickSort([3,4,51,51,14,22,13123,122]))