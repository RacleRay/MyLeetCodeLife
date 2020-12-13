package main

import (
	"time"
)

// 协程：轻量级线程
// 	非抢占式多任务处理，协程主动交出控制权；
// 	编译器/解释器/虚拟机层面的多任务，而不是操作系统层面的多任务
// 	多个协程可以在一个或者多个线程上执行
//
// 自程序是协程的一个特例 -- Donnald Knuth
//
// 检测race condition： go run -race xx.go
func main() {
	var a [10]int
	for i := 0; i < 10; i++ {
		go func(i int) {
			for {
				// fmt.Printf("Hello from goroutine %d \n", i)
				a[i]++ // race condition
			}
		}(i)
	}
	time.Sleep(time.Millisecond)
}
