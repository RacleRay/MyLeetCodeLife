package parser

import (
	"regexp"
	"simpleCrawler/engine"
)

const cityListRe = `<a href="(http://www.zhenai.com/zhenghun/[0-9a-z]+?)"[^>]*>([^<]+)</a>`

func ParseCityList(content []byte, _ string) engine.ParseResult {
	re := regexp.MustCompile(cityListRe)
	matches := re.FindAllSubmatch(content, -1)

	result := engine.ParseResult{}
	limit := 20
	for _, m := range matches {
		// fmt.Printf("City: %s, URL: %s\n", m[2], m[1])
		result.Request = append(result.Request,
			engine.Request{
				Url: string(m[1]),
				// ParseFunc: engine.NilParser,
				Parser: engine.NewFuncParser(
					ParserCity, "ParserCity"),
			})
		// result.Items = append(result.Items, "City "+string(m[2]))
		limit--
		if limit == 0 {
			break
		}
	}
	// fmt.Printf("Matches found: %d\n", len(matches))
	return result
}
