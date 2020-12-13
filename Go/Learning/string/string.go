package main

import (
	"fmt"
	"unicode/utf8"
)

func main() {
	s := "中文字符串处理"
	fmt.Println(s)
	fmt.Println()
	fmt.Println("===========")

	for i, by := range []byte(s) {
		fmt.Printf("(%d %X) ", i, by)
	}
	fmt.Println()
	fmt.Println("===========")
	for i, ch := range s {
		fmt.Printf("(%d %X) ", i, ch)
	}
	fmt.Println()
	fmt.Println("===========")

	bytes := []byte(s)
	for len(bytes) > 0 {
		ch, size := utf8.DecodeRune(bytes)
		bytes = bytes[size:]
		fmt.Printf("%c ", ch)
	}
	fmt.Println()
	fmt.Println("===========")

	for i, ch := range []rune(s) {
		fmt.Printf("(%d %c) ", i, ch)
	}
	fmt.Println()
	fmt.Println("Rune count: ", utf8.RuneCountInString(s))
}
