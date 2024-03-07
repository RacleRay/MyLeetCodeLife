#ifndef __CONN__H__
#define __CONN__H__

#include <ctime>
#include <string>

#include <mysql/mysql.h>


// better to uncopyable
class MysqlConnection {
public:
    MysqlConnection();

    ~MysqlConnection();

    bool connect(const std::string& ip, unsigned short port,
        const std::string& user, const std::string& pwd,
        const std::string& dbname);

    bool update(const std::string& sql);
    MYSQL_RES* query(const std::string& sql);

    void refresh_alive_time() { m_alive_time = clock(); };
    clock_t get_alive_time() { return clock() - m_alive_time; };

private:
    MYSQL* m_conn;
    clock_t m_alive_time;
};


#endif  //!__CONN__H__