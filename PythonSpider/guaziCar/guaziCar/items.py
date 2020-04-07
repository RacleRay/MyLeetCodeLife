# -*- coding: utf-8 -*-

# Define here the models for your scraped items
#
# See documentation in:
# https://docs.scrapy.org/en/latest/topics/items.html

import scrapy


class GuazicarItem(scrapy.Item):
    # define the fields for your item here like:
    # name = scrapy.Field()
    car_id = scrapy.Field()  # 车源号
    car_name = scrapy.Field()
    from_url = scrapy.Field()
    car_price = scrapy.Field()
    license_time = scrapy.Field()
    km_info = scrapy.Field()
    license_location = scrapy.Field()
    desplacement_info = scrapy.Field()  # 排量
    transmission_case = scrapy.Field()  # 手动挡还是自动挡