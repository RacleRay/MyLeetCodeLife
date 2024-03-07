from pymongo import MongoClient
from bson.objectid import ObjectId


class MongoDb:
    def __init__(self, host, username, password):
        self.__client = MongoClient(host=host, port=27017)
        self.__client.admin.authenticate(username, password)

    def insert(self, title, content):
        try:
            self.__client.news.contents.insert_one({"title": title, "content": content})
        except Exception as e:
            print(e)

    def search_id(self, title):
        try:
            news = self.__client.news.contents.find_one({"title": title})
            return str(news["_id"])
        except Exception as e:
            print(e)

    def update(self, id, title, content):
        try:
            self.__client.news.contents.update_one({"_id": ObjectId(id)},
                                                   {"$set": {"title": title, "content": content}})
        except Exception as e:
            print(e)

    def search_content_by_id(self, id):
        try:
            news = self.__client.news.contents.find_one({"_id": ObjectId(id)})
            return news["content"]
        except Exception as e:
            print(e)

    def delete_by_id(self, id):
        try:
            self.__client.news.contents.delete_one({"_id": ObjectId(id)})
        except Exception as e:
            print(e)
