package main

import "fmt"

func printArray(arr [5]int) {
	arr[0] = 100
	for i, v := range arr {
		fmt.Println(i, v)
	}
}

func printSlice(arr []int) {
	arr[0] = 100
	for i, v := range arr {
		fmt.Println(i, v)
	}
}

func main() {
	var arr1 [5]int
	arr2 := [5]int{1, 2, 3, 4, 5}
	arr3 := [...]int{1, 2, 3, 4, 5, 6}

	fmt.Println(arr1, arr2, arr3)

	var grid [4][5]int
	fmt.Println(grid)

	for i, v := range arr3 {
		fmt.Println(i, v)
	}

	// 数组值传递
	// printArray(arr2)
	// for i, v := range arr2 {
	// 	fmt.Println(i, v)
	// }

	// 切片: 是一个视图，共享数组储存位置
	slice1 := arr2[2:5]
	printSlice(slice1)

	slice2 := append(slice1, 7)
	fmt.Println(slice2)

	slice3 := make([]int, 10)
	slice4 := make([]int, 10, 16)
	fmt.Println(len(slice3), cap(slice3))
	fmt.Println(len(slice4), cap(slice4))

	copy(slice3, slice1)
	fmt.Println(slice3)

	// Map
	m := map[string]string{
		"name": "cc",
		"type": "hh",
	}
	fmt.Println(m)
	for k, v := range m {
		fmt.Println(k, v)
	}

	if name, ok := m["name"]; ok {
		fmt.Println(name)
	} else {
		fmt.Println("key not found")
	}
}
