import requests
import threading
import time
import pymongo
from multiprocessing import Queue
from lxml import etree


pageQueueEmpty = False
dataQueueEmpty = False


class MongoDB:
    def __init__(self, host, username, password):
        self.__client = pymongo.MongoClient(host=host, port=27017)
        self.__client.admin.authenticate(username, password)

    def insert(self, items):
        try:
            self.__client['jobInfoDb']['jobInfoCollection'].insert_many(items)
        except Exception as e:
            print(e)


class PageCrawler(threading.Thread):
    def __init__(self, thread_name, page_queue, data_queue):
        super(PageCrawler, self).__init__()
        self.thread_name = thread_name
        self.page_queue = page_queue
        self.data_queue = data_queue
        self.header = {
            "Accept": "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9",
            "Accept-Encoding": "gzip, deflate, br",
            "Accept-Language": "zh-CN,zh;q=0.9,en-GB;q=0.8,en;q=0.7",
            "Connection": "keep-alive",
            "Host": "search.51job.com",
            "Upgrade-Insecure-Requests": "1",
            "User-Agent": "Mozilla/5.0 (Windows NT 6.3; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/72.0.3610.2 Safari/537.36",
        }

    def run(self):
        print('当前启动的处理页码的任务为%s' % self.thread_name)
        while not pageQueueEmpty:
            try:
                # 队列为空时，block=FALSE会直接抛出异常而不会等待
                page = self.page_queue.get(block=False)  # 页码
                page_url = 'https://search.51job.com/list/000000,000000,0000,00,9,99,python,2,' + \
                    str(page)+'.html'
                print('当前的url为%s' % page_url)
                # proxy代理设置，需要自己准备代理服务器
                # TODO：申请代理服务器，比如 阿布云、站大爷等
                # proxy = {
                #     "http":"http://$name$:$pass$@http-dyn.abuyun.com:$port$",
                #     "https":"http://$name$:$pass$@http-dyn.abuyun.com:$port$",
                # }
                # response = requests.get(url=page_url, headers=self.header, proxies=proxy)
                response = requests.get(url=page_url, headers=self.header)
                response.encoding = 'gbk'
                self.data_queue.put(response.text)
                # time.sleep(3)
            except Exception as e:
                pass


mongoDB = MongoDB(host='192.168.1.68', username="rootsu", password="123456")


class ContentCrawler(threading.Thread):
    def __init__(self, thread_name, data_queue, lock):
        super(ContentCrawler, self).__init__()
        self.thread_name = thread_name
        self.data_queue = data_queue
        self.lock = lock

    def run(self):
        print("当前启动处理文本任务的线程为%s" % self.thread_name)
        while not dataQueueEmpty:
            try:
                text = self.data_queue.get(block=False)
                result = self.parse(text)
                with self.lock:
                    mongoDB.insert(result)
                    # time.sleep(3)
            except Exception as e:
                pass

    def parse(self, text):
        html = etree.HTML(text)
        all_div = html.xpath("//div[@id='resultList']//div[@class='el']")
        info_items = []
        for item in all_div:
            info = {}
            info['job_name'] = item.xpath("./p/span/a/@title")[0]
            info['company_name'] = item.xpath(
                ".//span[@class='t2']/a/@title")[0]
            info['company_address'] = item.xpath(
                ".//span[@class='t3']/text()")[0]
            try:
                info['money'] = item.xpath(".//span[@class='t4']/text()")[0]
            except IndexError:
                info['money'] = '工资缺失'
            info['date'] = item.xpath(".//span[@class='t5']/text()")[0]
            info_items.append(info)
        return info_items


def main():
    page_queue = Queue()
    data_queue = Queue()
    lock = threading.Lock()

    # crawl page number
    # TODO: 修改爬取量，爬取内容较多时，记得设置代理
    for page in range(1, 2):
        page_queue.put(page)
    print('当前页码队列的总量为%s' % page_queue.qsize())

    page_crawler_name = ["Page Crawler 1", "Page Crawler 2", "Page Crawler 3"]
    page_crawler_threads = []
    for name in page_crawler_name:
        page_crawler_thread = PageCrawler(name, page_queue, data_queue)
        page_crawler_thread.start()
        page_crawler_threads.append(page_crawler_thread)

    content_parser_name = ["Content Parser 1", "Content Parser 2", "Content Parser 3"]
    content_parser_threads = []
    for name in content_parser_name:
        content_parser_thread = ContentCrawler(name, data_queue, lock)
        content_parser_thread.start()
        content_parser_threads.append(content_parser_thread)

    # 线程退出
    global pageQueueEmpty
    global dataQueueEmpty
    while not page_queue.empty():
        pass
    pageQueueEmpty = True
    for page_crawler_thread in page_crawler_threads:
        page_crawler_thread.join()
        print(page_crawler_thread.thread_name,'处理结束')

    while not data_queue.empty():
        pass
    dataQueueEmpty = True
    for content_parser_thread in content_parser_threads:
        content_parser_thread.join()
        print(content_parser_thread.thread_name,"处理结束")


if __name__ == "__main__":
    main()

