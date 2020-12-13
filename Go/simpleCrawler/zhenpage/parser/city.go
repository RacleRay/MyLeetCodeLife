package parser

import (
	"regexp"
	"simpleCrawler/engine"
)

const cityRe = `<a href="(http://album.zhenai.com/u/[0-9]+)"[^>]*>([^<]+)</a>`

func ParserCity(content []byte, _ string) engine.ParseResult {
	re := regexp.MustCompile(cityRe)
	matches := re.FindAllSubmatch(content, -1)

	result := engine.ParseResult{}
	for _, m := range matches {
		// fmt.Printf("City: %s, URL: %s\n", m[2], m[1])
		// url := string(m[1])
		name := string(m[2])
		result.Request = append(result.Request,
			engine.Request{
				Url: string(m[1]),
				// ParseFunc: engine.NilParser,
				Parser: NewProfileParser(name),
			})
		// result.Items = append(result.Items, "User "+name)
	}
	// fmt.Printf("Matches found: %d\n", len(matches))
	return result
}
