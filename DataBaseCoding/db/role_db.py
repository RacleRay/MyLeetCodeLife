from db.mysql_db import pool


class RoleDb:
    def search_list(self):
        '查询角色类型'
        try:
            connection = pool.get_connection()
            cursor = connection.cursor()
            sql = "SELECT id,role FROM t_role"
            cursor.execute(sql)
            result = cursor.fetchall()
            return result
        except Exception as e:
            print(e)
        finally:
            if "connection" in dir():
                connection.close()