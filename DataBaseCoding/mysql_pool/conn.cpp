#include <iostream>

#include "conn.h"


MysqlConnection::MysqlConnection()
{
    m_conn = mysql_init(nullptr);
}

MysqlConnection::~MysqlConnection()
{
    if (m_conn != nullptr)
    {
        mysql_close(m_conn);
    }
}

bool MysqlConnection::connect(const std::string& ip, unsigned short port,
        const std::string& user, const std::string& pwd,
        const std::string& dbname)
{
    MYSQL *mp = mysql_real_connect(m_conn, ip.c_str(), user.c_str(), pwd.c_str(), dbname.c_str(), port, nullptr, 0);
    return mp != nullptr;
}

bool MysqlConnection::update(const std::string& sql)
{
    if (mysql_query(m_conn, sql.c_str()))
    {
        // naive log for example
        std::cout << "update failed" << std::endl; 
        return false;
    }    
    return true;
}

MYSQL_RES* MysqlConnection::query(const std::string& sql)
{
    if (mysql_query(m_conn, sql.c_str()))
    {
        // naive log for example
        std::cout << "query failed" << std::endl;
        return nullptr;
    }
    return mysql_use_result(m_conn);
}