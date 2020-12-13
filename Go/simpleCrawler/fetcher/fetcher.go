package fetcher

import (
	"bufio"
	"fmt"
	"io/ioutil"
	"net/http"
	"time"

	"log"

	"golang.org/x/net/html/charset"
	"golang.org/x/text/encoding"
	"golang.org/x/text/encoding/unicode"
	"golang.org/x/text/transform"
)

var rateLimit = time.Tick(100 * time.Millisecond)

func Fetch(url string) ([]byte, error) {
	// 引用同一个rateLimit，限制访问速率
	<-rateLimit
	resp, err := http.Get(url)
	if err != nil {
		panic(err)
	}
	defer resp.Body.Close()

	if resp.StatusCode != http.StatusOK {
		// fmt.Println("Error: status code ", resp.StatusCode)
		return nil, fmt.Errorf("wrong status code: %d", resp.StatusCode)
	}

	reader := bufio.NewReader(resp.Body)
	e := determineEncoder(reader)
	autoReader := transform.NewReader(reader,
		e.NewDecoder())

	return ioutil.ReadAll(autoReader)
}

// 识别网页编码格式
func determineEncoder(r *bufio.Reader) encoding.Encoding {
	bytes, err := r.Peek(1024)
	if err != nil {
		// panic(err)
		log.Printf("Fetcher error: %v", err)
		return unicode.UTF8
	}
	e, _, _ := charset.DetermineEncoding(bytes, "")
	return e
}
