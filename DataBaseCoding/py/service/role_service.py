from db.role_db import RoleDb


class RoleService:
    __role_db = RoleDb()
    def search_list(self):
        '角色类型列表'
        result = self.__role_db.search_list()
        return result