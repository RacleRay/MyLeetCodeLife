package main

import (
	"bufio"
	"fmt"
	"os"
)

func tryDefer() {
	defer fmt.Println("1")
	defer fmt.Println("2")

	// fmt.Println("1")
	// fmt.Println("2")

	fmt.Println("3")
	panic("error!")
	fmt.Println("4")
}

func fib() func() int {
	a, b := 0, 1
	return func() int {
		a, b = b, a+b
		return a
	}
}

func writeFile(filename string) {
	file, err := os.Create(filename)
	if err != nil {
		panic(err)
	}
	defer file.Close()

	writer := bufio.NewWriter(file)
	defer writer.Flush()

	f := fib()
	for i := 0; i < 20; i++ {
		fi := f()
		// fmt.Println(fi)
		fmt.Fprintf(writer, "%d\n", fi)
	}
}

func main() {
	// tryDefer()
	writeFile("fib.txt")
}
