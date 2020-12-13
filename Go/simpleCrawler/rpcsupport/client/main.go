package client

import (
	"log"
	"simpleCrawler/engine"
	"simpleCrawler/rpcsupport"
)

// 保存item的本地接口
func ItemSaver(host string) (chan engine.Item, error) {

	client, err := rpcsupport.NewClient(host)
	if err != nil {
		return nil, err
	}

	out := make(chan engine.Item)
	go func() {
		itemCount := 0
		for {
			item := <-out
			itemCount++
			log.Printf("Item Saver: Got item #%d: %v",
				itemCount, item)
			result := ""
			err := client.Call(rpcsupport.Config.ItemSaverRpc,
				item, &result)
			if err != nil {
				log.Printf("Item Saver: error saving item %v: %v", item, err)
			}
		}
	}()
	return out, nil
}
