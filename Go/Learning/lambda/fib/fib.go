package main

import (
	"bufio"
	"fmt"
	"io"
	"strings"
)

type intGen func() int

func fib() intGen {
	a, b := 0, 1
	return func() int {
		a, b = b, a+b
		return a
	}
}

// 为函数定义接口
func (gfunc intGen) Read(b []byte) (int, error) {
	next := gfunc()
	if next > 1000 {
		return 0, io.EOF
	}
	s := fmt.Sprintf("%d\n", next)
	return strings.NewReader(s).Read(b)
}

func printFileContents(reader io.Reader) {
	scanner := bufio.NewScanner(reader)
	for scanner.Scan() {
		fmt.Println(scanner.Text())
	}
}

func main() {
	f := fib()
	printFileContents(f)
}
