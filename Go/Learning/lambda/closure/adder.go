package main

import "fmt"

func adder() func(int) int {
	sum := 0
	return func(i int) int {
		sum += i
		return sum
	}
}

// python
// def adder():
// 	sum = 0
// 	def f(v):
// 		nonlocal sum
// 		sum += v
// 		return sum
// 	return f

// c++
// auto adder() ={
// 	auto sum = 0;
// 	return [=](int v) mutable {
// 		sum += v;
// 		return sum;
// 	};
// }

// 方法二
type iAdder func(int) (int, iAdder)

func adder2(base int) iAdder {
	return func(v int) (int, iAdder) {
		return base + v, adder2(base + v)
	}
}

func main() {
	a := adder2(0)
	for i := 1; i < 10; i++ {
		var s int
		s, a = a(i)
		fmt.Printf("0+...+%d=%d\n", i, s)
	}
}
