package worker

import (
	"errors"
	"fmt"
	"log"

	"simpleCrawler/engine"
	"simpleCrawler/rpcsupport"
	"simpleCrawler/zhenpage/parser"
)

type SerializedParser struct {
	Name string
	Args interface{}
}

// 储存序列化的请求，engine.Request储存未序列化的请求
type Request struct {
	Url    string
	Parser SerializedParser
}

// 储存序列化的结果，engine.Request储存未序列化的结果
type ParseResult struct {
	Items   []engine.Item
	Request []Request
}

func SerializeRequest(r engine.Request) Request {
	name, args := r.Parser.Serialize()
	return Request{
		Url: r.Url,
		Parser: SerializedParser{
			Name: name,
			Args: args,
		},
	}
}

func SerializeResult(r engine.ParseResult) ParseResult {
	result := ParseResult{
		Items: r.Items,
	}

	for _, req := range r.Request {
		result.Request = append(result.Request,
			SerializeRequest(req))
	}

	return result
}

func DeserializeRequest(r Request) (engine.Request, error) {
	parser, err := deserializeParser(r.Parser)
	if err != nil {
		return engine.Request{}, err
	}
	return engine.Request{
		Url:    r.Url,
		Parser: parser,
	}, nil
}

func DeserializeResult(r ParseResult) engine.ParseResult {
	result := engine.ParseResult{
		Items: r.Items,
	}

	for _, req := range r.Request {
		engineRequest, err := DeserializeRequest(req)
		if err != nil {
			log.Printf("error deserialize request: %v", err)
			continue
		}
		result.Request = append(result.Request, engineRequest)
	}

	return result
}

func deserializeParser(p SerializedParser) (engine.Parser, error) {
	switch p.Name {
	case rpcsupport.Config.ParseCityList:
		return engine.NewFuncParser(
			parser.ParseCityList, rpcsupport.Config.ParseCityList), nil
	case rpcsupport.Config.ParseCity:
		return engine.NewFuncParser(
			parser.ParserCity, rpcsupport.Config.ParseCity), nil
	case rpcsupport.Config.NilParser:
		return engine.NilParser{}, nil
	case rpcsupport.Config.ParseProfile:
		if userName, ok := p.Args.(string); ok {
			return parser.NewProfileParser(userName), nil
		} else {
			return nil, fmt.Errorf("invalid arg: %v", p.Args)
		}
	default:
		return nil, errors.New("Unknown Parser Name")
	}
}
