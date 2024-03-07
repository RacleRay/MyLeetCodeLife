#include <functional>
#include <iostream>

#include "conn_pool.h"


bool MysqlConnectionPool::load_config_file(const std::string& config_path)
{
    FILE *pf = fopen(config_path.c_str(), "r");
    if (pf == nullptr)
    {
        std::cout << "open config file failed" << std::endl;
        return false;
    }

    while (!feof(pf)) {
        char line[1024] = {0};
        fgets(line, 1024, pf);
        
        std::string str(line);
        int idx = str.find('=', 0);
        if (idx == -1) {
            continue;
        }

        int end_idx = str.find('\n', idx);
        std::string_view key = std::string_view(str.data(), idx);
        std::string_view value = std::string_view(str.data() + idx + 1, end_idx - idx - 1);

        if (key == "ip") {
            m_ip = value;
        } else if (key == "port") {
            m_port = std::stoi(std::string(value));
        } else if (key == "user") {
            m_user = value;
        } else if (key == "password") {
            m_password = value;
        } else if (key == "dbname") {
            m_dbname = value;
        } else if (key == "max_connection") {
            m_max_connection = std::stoi(std::string(value));
        } else if (key == "max_idle_time") {
            m_max_idle_time = std::stoi(std::string(value));
        } else if (key == "init_connection") {
            m_init_connection = std::stoi(std::string(value));
        } else if (key == "connection_timeout") {
            m_connection_timeout = std::stoi(std::string(value));
        }
    }

    return true;
}


MysqlConnectionPool::MysqlConnectionPool()
{
    if (!load_config_file("config.ini"))
    {
        return;
    }

    for (int i = 0; i < m_init_connection; ++i)
    {
        auto conn = new MysqlConnection();
        conn->refresh_alive_time();
        m_connection_queue.push(conn);
        m_connection_count++;
    }

    // produce start
    std::thread produce_thread(std::bind(&MysqlConnectionPool::produce_connection_task, this));
    produce_thread.detach();

    std::thread scanner_thread(std::bind(&MysqlConnectionPool::scanner_connection_task, this));
    scanner_thread.detach();
}


MysqlConnectionPool* MysqlConnectionPool::get_connection_pool()
{
    static MysqlConnectionPool pool;
    return &pool;
}

// consume connections
std::shared_ptr<MysqlConnection> MysqlConnectionPool::get_connection()
{
    std::unique_lock<std::mutex> lock(m_queue_mutex);
    while (m_connection_queue.empty()) {
        if (std::cv_status::timeout == m_cv.wait_for(lock, std::chrono::milliseconds(m_connection_timeout))) {
            if (m_connection_queue.empty()) {
                std::cout << "get connection timeout" << std::endl;
                return nullptr;
            }
        }
    }

    // auto recycle connections
    std::shared_ptr<MysqlConnection> sp(m_connection_queue.front(),
        [this](MysqlConnection* p) {
            std::unique_lock<std::mutex> lock(m_queue_mutex);
            p->refresh_alive_time();
            m_connection_queue.push(p);
        }
    );

    m_connection_queue.pop();
    m_cv.notify_all();

    return sp;
}

void MysqlConnectionPool::produce_connection_task()
{
    while (true) {
        std::unique_lock<std::mutex> lock(m_queue_mutex);
        while (!m_connection_queue.empty()) {
            m_cv.wait(lock);
        }

        if (m_connection_count < m_max_connection) {
            auto conn = new MysqlConnection();
            conn->refresh_alive_time();
            m_connection_queue.push(conn);
            m_connection_count++;
        }

        m_cv.notify_all();
    }
}

void MysqlConnectionPool::scanner_connection_task()
{
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(m_max_idle_time));

        std::unique_lock<std::mutex> lock(m_queue_mutex);
        while (m_connection_count > m_init_connection) {
            auto conn = m_connection_queue.front();
            if (conn->get_alive_time() >= (m_max_idle_time * 1000)) {
                m_connection_queue.pop();
                m_connection_count--;
                delete conn;
            } else {
                break;
            }
        }
    }
}



