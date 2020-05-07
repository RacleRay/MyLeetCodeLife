# -*- coding: utf-8 -*-

# Define here the models for your scraped items
#
# See documentation in:
# https://docs.scrapy.org/en/latest/topics/items.html

import scrapy


class SweethomeItem(scrapy.Item):
    # define the fields for your item here like:
    # name = scrapy.Field()
    content_name = scrapy.Field()
    content_id = scrapy.Field()
    content_url = scrapy.Field()
    upload_user = scrapy.Field()
    image_urls = scrapy.Field()  # scrapy默认抓取图片pipline的名称定义
    pic_name = scrapy.Field()
