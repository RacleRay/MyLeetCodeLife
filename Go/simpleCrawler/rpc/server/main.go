package main

import (
	rpcdemo "SimpleCrawler/rpc"
	"log"
	"net"
	"net/rpc"
	"net/rpc/jsonrpc"
)

// cmd: telnet localhost 1233
// 	{"method":"DemoService.Div", "params":[{"A":1,"B":2}], "id": 1}
func main() {
	rpc.Register(rpcdemo.DemoService{})
	listener, err := net.Listen("tcp", ":1234")
	if err != nil {
		panic(err)
	}
	for {
		conn, err := listener.Accept()
		if err != nil {
			log.Printf("accetp error: %v", err)
			continue
		}
		go jsonrpc.ServeConn(conn)
	}
}
