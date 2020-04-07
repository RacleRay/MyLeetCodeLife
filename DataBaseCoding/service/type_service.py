from db.type_db import TypeDb


class TypeService:
    __type_db = TypeDb()

    # 查询新闻类型列表
    def search_list(self):
        result = self.__type_db.search_list()
        return result
