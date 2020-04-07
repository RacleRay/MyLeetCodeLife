# -*- coding: utf-8 -*-
import scrapy
import re
from guaziCar.mongoDB import mongo
from guaziCar.items import GuazicarItem


class CarcrawlSpider(scrapy.Spider):
    name = 'carCrawl'
    allowed_domains = ['guazi.com']

    # start_urls = ['http://guazi.com/']

    def start_requests(self):
        while True:
            task = mongo.get_task(collection_name='guazi_task')
            if not task: break
            if '_id' in task:
                task.pop('_id')
            print('当前获取到的task为：%s' % task)
            if task['item_type'] == 'cars_page':
                yield scrapy.Request(url=task['task_url'],
                                     dont_filter=True,
                                     callback=self.handle_page,
                                     errback=self.handle_err,
                                     meta=task)
            elif task['item_type'] == 'car_info':
                yield scrapy.Request(url=task['car_url'],
                                     callback=self.handle_info,
                                     dont_filter=True,
                                     meta=task,
                                     errback=self.handle_err)

    def handle_err(self, failure):
        print(failure)
        mongo.save_task(failure.request.meta, 'guazi_task')

    def handle_page(self, response):
        if '为您找到0辆好车' in response.text: return
        cars_list = response.xpath("//ul[@class='carlist clearfix js-top']/li")
        for car_item in cars_list:
            info = {}
            info['car_name'] = car_item.xpath("./a/h2/text()").extract_first()
            info['car_url'] = 'https://www.guazi.com' + car_item.xpath("./a/@href").extract_first()
            info['item_type'] = 'car_info'
            yield scrapy.Request(url=info['car_url'],
                                 callback=self.handle_info,
                                 dont_filter=True,
                                 meta=info,
                                 errback=self.handle_err)
        if response.xpath("//ul[@class='pageLink clearfix']/li[last()]//span/text()").extract_first() == '下一页':
            # https://www.guazi.com/bj/audi-a8l/o1i7/
            value_search = re.compile("https://www.guazi.com/(.*?)/(.*?)/o(\d+)i7")
            try:
                value = value_search.findall(response.url)[0]
            except:
                print('下一页URL错误', response.url)
            # 下一页连接,response.request.meta字典的值覆盖了
            response.request.meta['task_url'] = 'https://www.guazi.com/%s/%s/o%si7' % (
                value[0], value[1], str(int(value[2]) + 1))
            # callback要调用handle_page
            yield scrapy.Request(url=response.request.meta['task_url'],
                                 callback=self.handle_page,
                                 meta=response.request.meta,
                                 dont_filter=True,
                                 errback=self.handle_err)

    def handle_info(self, response):
        car_id_search = re.compile(r"车源号：(.*?)\s+")
        car_info = GuazicarItem()
        car_info['car_id'] = car_id_search.search(response.text).group(1)
        car_info['car_name'] = response.request.meta['car_name']
        car_info['from_url'] = response.request.meta['car_url']
        car_info['car_price'] = response.xpath("//span[@class='pricestype']/text()").extract_first().strip()
        car_info['license_time'] = response.xpath(
            "//ul[@class='assort clearfix']/li[@class='one']/span/text()").extract_first().strip()
        car_info['km_info'] = response.xpath(
            "//ul[@class='assort clearfix']/li[@class='two']/span/text()").extract_first().strip()
        car_info['license_location'] = response.xpath(
            "//ul[@class='assort clearfix']/li[@class='three']/span/text()").extract()[0].strip()
        car_info['desplacement_info'] = response.xpath(
            "//ul[@class='assort clearfix']/li[@class='three']/span/text()").extract()[1].strip()
        car_info['transmission_case'] = response.xpath(
            "//ul[@class='assort clearfix']/li[@class='last']/span/text()").extract_first().strip()
        yield car_info
