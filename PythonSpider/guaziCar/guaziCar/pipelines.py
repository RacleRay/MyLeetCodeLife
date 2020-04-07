# -*- coding: utf-8 -*-

# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: https://docs.scrapy.org/en/latest/topics/item-pipeline.html
from guaziCar.mongoDB import mongo


class GuazicarPipeline(object):
    def process_item(self, item, spider):
        mongo.save_data(item, 'car_data')
        return item
