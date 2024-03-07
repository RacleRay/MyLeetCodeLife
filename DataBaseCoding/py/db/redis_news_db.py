import redis


class RedisDb:
    def __init__(self, host, password, max_connections):
        try:
            self.__pool = redis.ConnectionPool(
                host=host,
                port=6379,
                password=password,
                db=0,
                max_connections=max_connections
            )
        except Exception as e:
            print(e)

    def insert(self, id, title, username, type, content, is_top, create_time):
        connection = redis.Redis(connection_pool=self.__pool)
        try:
            connection.hmset(id, {
                "title": title,
                "author": username,
                "type": type,
                "content": content,
                "is_top": is_top,
                "create_time": create_time
            })
            if is_top:
                connection.expire(id, 24 * 60 * 60)
        except Exception as e:
            print(e)
        finally:
            del connection

    def delete_cache(self, id):
        connection = redis.Redis(connection_pool=self.__pool)
        try:
            connection.delete(id)
        except Exception as e:
            print(e)
        finally:
            del connection
