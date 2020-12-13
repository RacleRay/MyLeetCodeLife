package rpcsupport

import (
	"log"
	"net"
	"net/rpc"
	"net/rpc/jsonrpc"
)

func ServerRpc(service interface{}, host string) error {
	err := rpc.Register(service)
	if err != nil {
		return err
	}
	listener, err := net.Listen("tcp", host)
	if err != nil {
		// panic(err)
		return err
	}
	log.Printf("Listening on %s", host)

	for {
		conn, err := listener.Accept()
		if err != nil {
			log.Printf("accetp error: %v", err)
			continue
		}
		go jsonrpc.ServeConn(conn)
	}
	return nil
}

func NewClient(host string) (*rpc.Client, error) {
	conn, err := net.Dial("tcp", ":1234")
	if err != nil {
		return nil, err
	}
	client := jsonrpc.NewClient(conn)
	return client, nil
}
