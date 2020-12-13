package worker

import (
	"simpleCrawler/engine"
)

type CrawlService struct{}

// rpc 通信逻辑
func (CrawlService) Process(req Request, result *ParseResult) error {
	engineRequest, err := DeserializeRequest(req)
	if err != nil {
		return err
	}

	engineResult, err2 := engine.Worker(engineRequest)
	if err != nil {
		return err2
	}

	*result = SerializeResult(engineResult)
	return nil
}
