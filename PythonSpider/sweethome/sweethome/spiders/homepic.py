# -*- coding: utf-8 -*-
import scrapy
import re
import json
from sweethome.items import SweethomeItem


class HomepicSpider(scrapy.Spider):
    name = 'homepic'
    allowed_domains = ['xiaoguotu.to8to.com']
    start_urls = ['https://xiaoguotu.to8to.com/tuce/']

    def parse(self, response):
        # 解析用于读取ajax动态响应的url资源链接的id
        content_id_search = re.compile(r'(\d+)\.html')
        # response就是一个Html对象
        content_text = response.xpath("//div[@class='item']//div/a/text()").extract()
        content_href = response.xpath("//div[@class='item']//div/a/@href").extract()
        for name, href in zip(content_text, content_href):
            info = {}
            info['content_name'] = name
            # 目标图片的URL
            info['content_id'] = content_id_search.search(href).group(1)
            info['content_ajax_url'] = 'https://xiaoguotu.to8to.com/case/list?a2=0&a12=&a11=' + \
                str(info['content_id']) + '&a1=0&a17=1'
            yield scrapy.Request(info['content_ajax_url'], callback=self.process_info, meta=info)

        # 下一页
        # if response.xpath("//a[@id='nextpageid']"):
        #     page_id = int(response.xpath(
        #         "//div[@class='pages']/strong/text()").extract_first())
        #     nextpage_url = 'https://xiaoguotu.to8to.com/tuce/p_%d.html' % (
        #         page_id + 1)
        #     yield scrapy.Request(nextpage_url, callback=self.parse)

    def process_info(self, response):
        meta_data = json.loads(response.text)['dataImg']
        for item in meta_data:
            for pic_info in item['album']:
                home_info = SweethomeItem()
                home_info['upload_user'] = pic_info['l']['n']
                home_info['image_urls'] = ['https://pic1.to8to.com/case/' + pic_info['l']['s']]
                home_info['pic_name'] = pic_info['l']['t']
                home_info['content_name'] = response.request.meta['content_name']
                home_info['content_id'] = response.request.meta['content_id']
                home_info['content_url'] = response.request.meta['content_ajax_url']
                # 进入pipline处理
                yield home_info
