package server

import (
	"flag"
	"fmt"
	"simpleCrawler/rpcsupport"
	"simpleCrawler/rpcsupport/worker"
)

var port = flag.Int("port", 0, "the port to listen on")

// 启动爬虫worker的函数
func main() {
	flag.Parse()
	if *port == 0 {
		fmt.Println("Need a port")
		return
	}
	err := rpcsupport.ServerRpc(
		worker.CrawlService{}, fmt.Sprintf(":%d", *port))
	if err != nil {
		panic(err)
	}
}
