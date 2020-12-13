package parser

import (
	"io/ioutil"
	"testing"
)

func TestParseCityList(t *testing.T) {
	// content, err := fetcher.Fetch("http://www.zhenai.com/zhenghun")
	content, err := ioutil.ReadFile("test_data.html")

	if err != nil {
		panic(err)
	}

	// fmt.Printf("%s\n", content)
	result := ParseCityList(content)

	const resSize = 470
	// expectedCities := []string{
	// 	"City 阿坝", "City 阿克苏", "City 阿拉善盟",
	// }

	if len(result.Request) != resSize {
		t.Errorf("Result size is: %d, but should be: %d",
			len(result.Request),
			resSize)
	}
	// for i, city := range expectedCities {
	// 	if result.Items[i].(string) != city {
	// 		t.Errorf("Find city is: %d %s, but should be: %s",
	// 			i, result.Items[i].(string), city)
	// 	}
	// }
}
