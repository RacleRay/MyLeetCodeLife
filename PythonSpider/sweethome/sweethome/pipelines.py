# -*- coding: utf-8 -*-

# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: https://docs.scrapy.org/en/latest/topics/item-pipeline.html
import pymongo
from scrapy.exceptions import DropItem
from scrapy.pipelines.images import ImagesPipeline


class SweethomePipeline(object):
    def __init__(self):
        self.__client = pymongo.MongoClient(host='192.168.1.68', port=27017)
        self.__client.admin.authenticate("rootsu", "123456")
        self.collection = self.__client['sweethome']['metadata']

    def process_item(self, item, spider):
        data = dict(item)
        self.collection.insert_one(data)
        return item


class SweethomeImagesPipeline(ImagesPipeline):
    """默认使用self.get_media_requests(self, item, info)根据image_urls中指定的URL进行爬取。
       图片下载完毕之后，处理结果的,返回是一个二元组(success, image_info_or_failure)"""

    def item_completed(self, results, item, info):
        image_paths = [x['path'] for ok, x in results if ok]
        if not image_paths:
            raise DropItem('Item contains no images')
        return item

    def file_path(self, request, response=None, info=None):
        url = request.url
        file_name = url.split('/')[-1]
        return file_name