from db.mysql_db import pool


class UserDb:
    def __excute(self, sql_query, *args, rollback=False, commit=False):
        try:
            connection = pool.get_connection()
            cursor = connection.cursor()
            sql = sql_query
            cursor.execute(sql, args)
            if commit:
                connection.commit()
            return cursor, connection
        except Exception as e:
            print(e)
            if rollback and "connection" in dir():
                connection.rollback()
            if "connection" in dir():
                connection.close()

    def login(self, username, password):
        sql = "SELECT COUNT(*) FROM t_user WHERE username=%s AND " \
              "AES_DECRYPT(UNHEX(password),'HelloWorld')=%s"
        cursor, connection = self.__excute(sql, username, password)
        count = cursor.fetchone()[0]
        if "connection" in dir():
            connection.close()
        return True if count == 1 else False

    def search_user_role(self, username):
        sql = "SELECT r.role FROM t_user u JOIN t_role r ON u.role_id=r.id " \
              "WHERE u.username=%s"
        cursor, connection = self.__excute(sql, username)
        role = cursor.fetchone()[0]
        if "connection" in dir():
            connection.close()
        return role

    def insert(self, username, password, email, role_id):
        sql = "INSERT INTO t_user(username,password,email,role_id) " \
              "VALUES(%s,HEX(AES_ENCRYPT(%s,'HelloWorld')),%s,%s)"
        _, connection = self.__excute(sql, username, password, email, role_id, rollback=True, commit=True)
        if "connection" in dir():
            connection.close()

    def search_count_page(self):
        '查询用户总页数'
        sql = "select ceil(count(*)/10) from t_user"
        cursor, connection = self.__excute(sql)
        count_pages = cursor.fetchone()[0]
        if "connection" in dir():
            connection.close()
        return count_pages

    def search_list(self, page):
        '查询用户分页记录'
        sql = "SELECT u.id,u.username,r.role " \
              "FROM t_user u JOIN t_role r " \
              "ON u.role_id=r.id " \
              "ORDER BY u.id " \
              "LIMIT %s,%s"
        cursor, connection = self.__excute(sql, (page - 1) * 10, 10)
        result = cursor.fetchall()
        if "connection" in dir():
            connection.close()
        return result

    def update(self, id, username, password, email, role_id):
        '修改信息'
        sql = "UPDATE t_user SET username=%s," \
              "password=HEX(AES_ENCRYPT(%s,'HelloWorld'))," \
              "email=%s,role_id=%s " \
              "WHERE id=%s"
        _, connection = self.__excute(sql, username, password, email, role_id, id, rollback=True, commit=True)
        if "connection" in dir():
            connection.close()

    def delete_by_id(self, id):
        sql = "DELETE FROM t_user WHERE id=%s"
        _, connection = self.__excute(sql, id, rollback=True, commit=True)
        if "connection" in dir():
            connection.close()

    def search_userid(self,username):
        sql = "SELECT id FROM t_user WHERE username=%s"
        cursor, connection = self.__excute(sql, username)
        uid = cursor.fetchone()[0]
        if "connection" in dir():
            connection.close()
        return uid