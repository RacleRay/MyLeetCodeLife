import pymongo


class MongoDB:
    def __init__(self, host, username, password):
        _client = pymongo.MongoClient(host=host, port=27017)
        _client.admin.authenticate(username, password)
        self.__client = _client['guaziDB']

    def save_task(self, task, collection_name):
        print('当前存储的task为%s:' % task)
        self.__client[collection_name].insert_one(dict(task))

    def get_task(self, collection_name):
        return self.__client[collection_name].find_one_and_delete({})

    def save_data(self, data, collection_name):
        print('当前存储的数据为%s:' % data)
        data = dict(data)
        self.__client[collection_name].update({'car_id': data['car_id']}, data, True)


mongo = MongoDB(host='192.168.1.68', username="rootsu", password="123456")
