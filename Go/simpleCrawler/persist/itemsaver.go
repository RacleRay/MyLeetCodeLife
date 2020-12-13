package persist

import (
	"context"
	"errors"
	"log"
	"simpleCrawler/engine"

	"gopkg.in/olivere/elastic.v5"
)

func ItemSaver(index string) (chan engine.Item, error) {
	// http.Post
	// go get -v gopkg.in/olivere/elastic.v5
	client, err := elastic.NewClient(
		elastic.SetSniff(false))
	if err != nil {
		return nil, err
	}

	out := make(chan engine.Item)
	go func() {
		itemCount := 0
		for {
			item := <-out
			itemCount++
			log.Printf("Item saver got: #%d, %v", itemCount, item)
			err := Save(client, item, index)
			if err != nil {
				log.Printf("Error: item save %v, %v", item, err)
			}
		}
	}()
	return out, nil
}

func Save(client *elastic.Client, item engine.Item,
	index string) error {

	if item.Type == "" {
		return errors.New("No Type")
	}
	indexServer := client.Index().
		Index(index).
		Type(item.Type).
		BodyJson(item)
	if item.Id != "" {
		indexServer.Id(item.Id)
	}
	_, err2 := indexServer.
		Do(context.Background())
	if err2 != nil {
		return err2
	}
	// fmt.Println(resp)
	return nil
}
