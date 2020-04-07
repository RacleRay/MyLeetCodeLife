from db.mysql_db import pool


class NewsDb:
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

    def search_unreview_list(self, page):
        '查看待审批列表'
        sql = "SELECT n.id,n.title,t.type,u.username " \
              "FROM t_news n JOIN t_type t ON n.type_id=t.id " \
              "JOIN t_user u ON n.editor_id=u.id " \
              "WHERE n.state=%s " \
              "ORDER BY n.create_time DESC " \
              "LIMIT %s,%s"
        cursor, connection = self.__excute(sql, "待审批", (page - 1) * 10, 10)
        if "connection" in dir():
            connection.close()
        return cursor.fetchall()

    def search_unreview_count_page(self):
        '查询待审批新闻的总页数'
        sql = "SELECT CEIL(COUNT(*)/10) FROM t_news WHERE state=%s"
        cursor, connection = self.__excute(sql, "待审批")
        count_page = cursor.fetchone()[0]
        if "connection" in dir():
            connection.close()
        return count_page

    def update_unreview_news(self, id):
        '审批新闻'
        sql = "UPDATE t_news SET state=%s WHERE id=%s"
        _, connection = self.__excute(sql, "已审批", id, rollback=True, commit=True)
        if "connection" in dir():
            connection.close()

    def search_list(self, page):
        '查询新闻列表'
        sql = "SELECT n.id,n.title,t.type,u.username " \
              "FROM t_news n JOIN t_type t ON n.type_id=t.id " \
              "JOIN t_user u ON n.editor_id=u.id " \
              "ORDER BY n.create_time DESC " \
              "LIMIT %s,%s"
        cursor, connection = self.__excute(sql, (page - 1) * 10, 10)
        result = cursor.fetchall()
        if "connection" in dir():
            connection.close()
        return result

    def search_count_page(self):
        '查询新闻总页数'
        sql = "SELECT CEIL(COUNT(*)/10) FROM t_news"
        cursor, connection = self.__excute(sql)
        count_page = cursor.fetchone()[0]
        if "connection" in dir():
            connection.close()
        return count_page

    def delete_by_id(self, id):
        '删除新闻'
        sql = "DELETE FROM t_news WHERE id=%s"
        _, connection = self.__excute(sql, id, rollback=True, commit=True)
        connection.close()

    def insert(self, title, editor_id, type_id, content_id, is_top):
        sql = "INSERT INTO t_news(title,editor_id,type_id,content_id,is_top,state) " \
              "VALUES(%s,%s,%s,%s,%s,%s)"
        _, connection = self.__excute(sql, title, editor_id, type_id, content_id, is_top, "待审批", rollback=True,
                                      commit=True)
        if "connection" in dir():
            connection.close()

    def search_cache(self, id):
        '查找保存的详细新闻信息'
        sql = "SELECT n.title,u.username,t.type,n.content_id," \
              "n.is_top,n.create_time " \
              "FROM t_news n " \
              "JOIN t_type t ON n.type_id=t.id " \
              "JOIN t_user u ON n.editor_id=u.id " \
              "WHERE n.id=%s"
        cursor, connection = self.__excute(sql, id)
        result = cursor.fetchone()
        if "connection" in dir():
            connection.close()
        return result

    def search_by_id(self, id):
        '根据id查找新闻'
        sql = "SELECT n.title,t.type,n.is_top, n.content_id " \
              "FROM t_news n " \
              "JOIN t_type t ON n.type_id=t.id " \
              "WHERE n.id=%s"
        cursor, connection = self.__excute(sql, id)
        result = cursor.fetchone()
        if "connection" in dir():
            connection.close()
        return result

    def update(self, id, title, type_id, content_id, is_top):
        '更改新闻'
        sql = "UPDATE t_news SET title=%s,type_id=%s,content_id=%s," \
              "is_top=%s,state=%s,update_time=NOW() WHERE id=%s"
        _, connection = self.__excute(sql, title, type_id, content_id, is_top, "待审批", id, rollback=True, commit=True)
        if "connection" in dir():
            connection.close()

    def search_content_id(self, id):
        '查找mongodb中的content保存id'
        sql = "SELECT content_id FROM t_news " \
              "WHERE id=%s"
        cursor, connection = self.__excute(sql, id)
        content_id = cursor.fetchone()[0]
        if "connection" in dir():
            connection.close()
        return content_id
