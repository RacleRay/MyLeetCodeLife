package parser

import (
	"regexp"
	"simpleCrawler/engine"
	"simpleCrawler/model"
	"strconv"
)

var ageRe = regexp.MustCompile(`<td><span class="label">年龄：</span>(\d+)岁?</td>`)
var genderRe = regexp.MustCompile(`<td><span class="label">性别：</span><span field="">([^<]+)</span></td>`)
var idRe = regexp.MustCompile(`http://album.zhenai.com/u/([0-9]+)`)

func ParseProfile(content []byte, name string,
	url string) engine.ParseResult {
	profile := model.Profile{}
	profile.Name = name

	age, err := strconv.Atoi(
		extractString(content, ageRe))
	if err == nil {
		profile.Age = age
	}

	profile.Gender = extractString(content, genderRe)

	result := engine.ParseResult{
		Items: []engine.Item{
			{
				Url:     url,
				Type:    "zhenai",
				Id:      extractString([]byte(url), idRe),
				Payload: profile,
			},
		},
	}
	return result
}

func extractString(content []byte, re *regexp.Regexp) string {
	match := re.FindSubmatch(content)
	if len(match) >= 2 {
		return string(match[1])
	} else {
		return ""
	}
}

// func ProfileParser(name string, url string) func([]byte) engine.ParseResult {
// 	return func(c []byte) engine.ParseResult {
// 		return ParseProfile(c, name, url)
// 	}
// }

type ProfileParser struct {
	userName string
}

func (p *ProfileParser) Parse(contents []byte, url string) engine.ParseResult {
	return ParseProfile(contents, url, p.userName)
}

func (p *ProfileParser) Serialize() (name string, args interface{}) {
	return "ParseProfile", p.userName
}

func NewProfileParser(name string) *ProfileParser {
	return &ProfileParser{
		userName: name,
	}
}
