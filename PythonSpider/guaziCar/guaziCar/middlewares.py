# -*- coding: utf-8 -*-

# Define here the models for your spider middleware
#
# See documentation in:
# https://docs.scrapy.org/en/latest/topics/spider-middleware.html

import re
import execjs
from scrapy import signals
from guaziCar.mongoDB import mongo


class GuazicarDownloaderMiddleware(object):
    # Not all methods need to be defined. If a method is not defined,
    # scrapy acts as if the downloader middleware does not modify the
    # passed objects.
    def __init__(self):
        with open('extracted_js.js', 'r', encoding='utf-8') as f:
            self.f_read = f.read()

    @classmethod
    def from_crawler(cls, crawler):
        # This method is used by Scrapy to create your spiders.
        s = cls()
        crawler.signals.connect(s.spider_opened, signal=signals.spider_opened)
        return s

    def process_request(self, request, spider):
        """guazi网站会记录对话的agent的浏览器信息，所以不能随机选取。设置为固定，在settings.py中设置了，此处就不需要设置。"""
        # Called for each request that goes through the downloader
        # middleware.

        # Must either:
        # - return None: continue processing this request
        # - or return a Response object
        # - or return a Request object
        # - or raise IgnoreRequest: process_exception() methods of
        #   installed downloader middleware will be called
        # Options：添加代理，在网上申请爬虫代理
        return None

    def process_response(self, request, response, spider):
        # Called with the response returned from the downloader.

        # Must either;
        # - return a Response object
        # - return a Request object
        # - or raise IgnoreRequest
        # 处理js混淆
        if '正在打开中,请稍后' in response.text:
            value_search = re.compile(r"anti\('(.*?)','(.*?)'\);")
            string = value_search.search(response.text).group(1)
            key = value_search.search(response.text).group(2)
            js = execjs.compile(self.f_read)
            js_return = js.call('anti', string, key)
            cookie = {'antipas': js_return}  # 字典格式
            request.cookie = cookie
            return request  # 再次由调度器请求
        elif response.status == 200:
            return response
        elif '请求太频繁' in response.text:
            return request

    def process_exception(self, request, exception, spider):
        # Called when a download handler or a process_request()
        # (from other downloader middleware) raises an exception.

        # Must either:
        # - return None: continue processing this exception
        # - return a Response object: stops process_exception() chain
        # - return a Request object: stops process_exception() chain
        pass

    def spider_opened(self, spider):
        spider.logger.info('Spider opened: %s' % spider.name)
