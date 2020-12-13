package persist

import (
	"log"
	"simpleCrawler/engine"
	"simpleCrawler/persist"

	"gopkg.in/olivere/elastic.v5"
)

type ItemSaverService struct {
	Client *elastic.Client
	Index  string
}

//
func (s *ItemSaverService) Save(item engine.Item, result *string) error {
	err := persist.Save(s.Client, item, s.Index)
	if err == nil {
		*result = "ok"
		log.Printf("Item %v saved.", item)
	} else {
		log.Printf("Error saving item %v: %v", item, err)
	}
	return err
}
