#ifndef __CONN_POOL__H__
#define __CONN_POOL__H__

#include <queue>
#include <thread>
#include <condition_variable>

#include "conn.h"


class MysqlConnectionPool {
public:
    static MysqlConnectionPool* get_connection_pool();

    // return avalible conncetion
    std::shared_ptr<MysqlConnection> get_connection();

private:
    MysqlConnectionPool();

    MysqlConnectionPool(const MysqlConnectionPool&) = delete;
    MysqlConnectionPool& operator=(const MysqlConnectionPool&) = delete;

    MysqlConnectionPool(MysqlConnectionPool&&) = delete;
    MysqlConnectionPool& operator=(MysqlConnectionPool&&) = delete;

    bool load_config_file(const std::string& config_path);

    void produce_connection_task();  // task for producer thread

    void scanner_connection_task();  // task for recycling idle connections

private:
    std::string m_ip;
    unsigned short m_port;
    std::string m_user;
    std::string m_password;
    std::string m_dbname;

    int m_init_connection;  // initial size of connection pool
    int m_max_connection;   // max size of connection pool
    int m_max_idle_time;   // max idle time of a connection before recycled
    int m_connection_timeout;  // max time to establish a connection

    std::queue<MysqlConnection*> m_connection_queue;
    std::mutex m_queue_mutex;
    std::atomic_int m_connection_count;
    std::condition_variable m_cv;
};


#endif  //!__CONN_POOL__H__