package main

import (
	"SimpleCrawler/rpcsupport"
	"SimpleCrawler/rpcsupport/persist"
	"flag"
	"fmt"

	"gopkg.in/olivere/elastic.v5"
)

var port = flag.Int("port", 0, "the port to listen on")

// 保存item的远程server启动函数
func main() {
	flag.Parse()
	if *port == 0 {
		fmt.Println("Need a port")
		return
	}
	err := serve(fmt.Sprintf(":%d", *port),
		rpcsupport.Config.ElasticIndex)
	if err != nil {
		panic(err)
	}
}

func serve(host, index string) error {
	client, err := elastic.NewClient(
		elastic.SetSniff(false))
	if err != nil {
		return err
	}
	return rpcsupport.ServerRpc(
		persist.ItemSaverService{
			Client: client,
			Index:  index,
		},
		host)
}
