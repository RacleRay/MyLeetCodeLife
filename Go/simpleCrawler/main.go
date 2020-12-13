package main

import (
	"flag"
	"log"
	"net/rpc"
	"simpleCrawler/engine"
	"simpleCrawler/rpcsupport"
	itemSaver "simpleCrawler/rpcsupport/client"
	worker "simpleCrawler/rpcsupport/worker/client"
	"simpleCrawler/scheduler"
	"simpleCrawler/zhenpage/parser"
	"strings"
)

// 注意GOPATH的src文件夹下是否存在代码文件夹
// go get golang.org/x/net/html
// go get golang.org/x/text

var (
	itemSaverHost = flag.String(
		"itemSaver_host", "", "itemSaver host")
	workerHosts = flag.String(
		"worker_hosts", "", "worker hosts (comma “,” separated)")
)

func main() {
	// engine.SimpleEngine{}.Run(engine.Request{
	// 	Url:       "http://www.zhenai.com/zhenghun",
	// 	ParseFunc: parser.ParseCityList,
	// })

	// e := engine.ConcurrentEngine{
	// 	Scheduler:   &scheduler.SimpleScheduler{},
	// 	WorkerCount: 10,
	// }
	// e.Run(engine.Request{
	// 	Url:       "http://www.zhenai.com/zhenghun",
	// 	ParseFunc: parser.ParseCityList,
	// })

	// itemChan, err := persist.ItemSaver("SimpleCrawler")
	// if err != nil {
	// 	panic(err)
	// }
	// e := engine.ConcurrentEngine{
	// 	Scheduler:   &scheduler.QueueScheduler{},
	// 	WorkerCount: 10,
	// 	ItemChan:    itemChan,
	// }
	// e.Run(engine.Request{
	// 	Url:       "http://www.zhenai.com/zhenghun",
	// 	ParseFunc: parser.ParseCityList,
	// })

	flag.Parse()
	itemChan, err := itemSaver.ItemSaver(rpcsupport.Config.ItemSaverPort)
	if err != nil {
		panic(err)
	}

	pool := createClientPool(strings.Split(*workerHosts, ","))

	processor := worker.CreateProcessor(pool)

	e := engine.ConcurrentEngine{
		Scheduler:        &scheduler.QueueScheduler{},
		WorkerCount:      10,
		ItemChan:         itemChan,
		RequestProcessor: processor,
	}
	e.Run(engine.Request{
		Url: "http://www.zhenai.com/zhenghun",
		Parser: engine.NewFuncParser(
			parser.ParseCityList, "ParseCityList"),
	})

}

func createClientPool(hosts []string) chan *rpc.Client {
	var clients []*rpc.Client
	for _, h := range hosts {
		client, err := rpcsupport.NewClient(h)
		if err == nil {
			clients = append(clients, client)
			log.Panicf("Connected to %s", h)
		} else {
			log.Panicf(
				"error connecting to %s: %v", h, err)
		}
	}

	out := make(chan *rpc.Client)
	go func() {
		for {
			for _, client := range clients {
				out <- client
			}
		}
	}()
	return out
}
