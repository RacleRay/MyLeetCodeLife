from db.news_db import NewsDb
from db.redis_news_db import RedisDb
from db.mongo_news_db import MongoDb

class NewsService:
    __news_db = NewsDb()
    __redis_db = RedisDb(host='192.168.1.68', password='123456', max_connections=10)
    __mongo_db = MongoDb(host='192.168.1.68', username="rootsu", password="123456")

    def search_unreview_list(self, page):
        '查询待审批新闻列表'
        result = self.__news_db.search_unreview_list(page)
        return result

    def search_unreview_count_page(self):
        '查询待审批新闻的总页数'
        count_page = self.__news_db.search_unreview_count_page()
        return count_page

    def update_unreview_news(self, id):
        '审批新闻'
        self.__news_db.update_unreview_news(id)

    def search_list(self, page):
        '查询新闻列表'
        result = self.__news_db.search_list(page)
        return result

    def search_count_page(self):
        '查询新闻总页数'
        count_page = self.__news_db.search_count_page()
        return count_page

    def delete_by_id(self, id):
        '删除新闻，mysql中的元信息和mongodb中的content'
        self.__news_db.delete_by_id(id)
        content_id = self.__news_db.search_content_id(id)
        self.__mongo_db.delete_by_id(content_id)

    def insert(self, title, editor_id, type_id, content, is_top):
        self.__mongo_db.insert(title, content)
        content_id = self.__mongo_db.search_id(title)
        self.__news_db.insert(title, editor_id, type_id, content_id, is_top)

    def search_cache(self, id):
        '查找保存的详细新闻信息'
        result = self.__news_db.search_cache(id)
        return result

    def cache_news(self, id, titile, username, type, content, is_top, create_time):
        '向Redis保存缓存的新闻'
        self.__redis_db.insert(id, titile, username, type, content, is_top, create_time)

    def delete_cache(self, id):
        '删除缓存的新闻'
        self.__redis_db.delete_cache(id)

    def search_by_id(self, id):
        '根据id查找新闻'
        result = self.__news_db.search_by_id(id)
        return result

    def update(self, id, title, type_id, content, is_top):
        '更改新闻'
        content_id = self.__news_db.search_content_id(id)
        self.__mongo_db.update(content_id, title, content)
        self.__news_db.update(id, title, type_id, content_id, is_top)
        self.delete_cache(id)

    def search_content_by_id(self, id):
        content = self.__mongo_db.search_content_by_id(id)
        return content