package main

import (
	rpcdemo "SimpleCrawler/rpc"
	"fmt"
	"net"
	"net/rpc/jsonrpc"
)

func main() {
	conn, err := net.Dial("tcp", ":1234")
	if err != nil {
		panic(err)
	}
	client := jsonrpc.NewClient(conn)

	var result float64
	err2 := client.Call("DemoService.Div", rpcdemo.Args{1, 2}, &result)
	fmt.Println(result, err2)
}
