// 带有类型检查的duck typing
// 使用者定义接口
package main

import (
	mock "Learning/duck/mock"
	real "Learning/duck/realMock"
	"time"

	"fmt"
)

type Retriever interface {
	Get(url string) string
}

type Poster interface {
	Post(url string, form map[string]string) string
}

type RetrieverPoster interface {
	Retriever
	Poster
}

func download(r Retriever) string {
	return r.Get("http://www.baidu.com")
}

func post(poster Poster) {
	poster.Post("http://www.baidu.com",
		map[string]string{
			"name": "haha",
			"age":  "12",
		})
}

func session(rp RetrieverPoster) string {
	rp.Post("http://www.baidu.com",
		map[string]string{
			"name": "changed",
			"age":  "12",
		})

	return rp.Get("http://www.baidu.com")
}

func inspect(r Retriever) {
	fmt.Printf("%T %v\n", r, r)
	// type switch
	switch v := r.(type) {
	case *mock.Retriever:
		fmt.Println("Contents: ", v.Contents)
	case *real.Retriever:
		fmt.Println("UserAgent: ", v.UserAgent)
	}
}

func main() {
	var r Retriever
	r = &mock.Retriever{"fake message."}
	inspect(r)
	// fmt.Println(download(r))

	r = &real.Retriever{
		UserAgent: "Mozilla/5.0 (Macintosh; Intel Mac OS X 10)",
		TimeOut:   time.Second,
	}
	inspect(r)
	// fmt.Println(download(r))

	// type assertion
	if mockRetriever, ok := r.(*mock.Retriever); ok {
		fmt.Println(mockRetriever.Contents)
	} else {
		fmt.Println("Not a mock.Retriever")
	}

	combined := &mock.Retriever{"before changed"}
	fmt.Println("Session call:")
	fmt.Println(session(combined))

}
