package client

import (
	"net/rpc"
	"simpleCrawler/engine"
	"simpleCrawler/rpcsupport"
	"simpleCrawler/rpcsupport/worker"
)

// chan 调用多个worker的服务
func CreateProcessor(clientChan chan *rpc.Client) engine.Processor {

	return func(req engine.Request) (engine.ParseResult, error) {
		serializedRequest := worker.SerializeRequest(req)

		var serializedResult worker.ParseResult
		c := <-clientChan
		err := c.Call(rpcsupport.Config.CrawlServiceRpc,
			serializedRequest, &serializedResult)
		if err != nil {
			return engine.ParseResult{}, err
		}

		return worker.DeserializeResult(serializedResult), nil
	}

}
