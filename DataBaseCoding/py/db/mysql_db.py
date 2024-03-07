import mysql.connector.pooling


__all__ = ['pool']

__config__ = {
    "host": "192.168.1.68",
    "port": 3306,
    "user": "root",
    "password": "200923He@",
    "database": "news"
}

try:
    pool = mysql.connector.pooling.MySQLConnectionPool(
        **__config__,
        pool_size=10
    )
except Exception as e:
    print(e)
