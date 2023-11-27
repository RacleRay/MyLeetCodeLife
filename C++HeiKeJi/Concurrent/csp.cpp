#include <iostream>
#include <future>
#include <queue>
#include <mutex>
#include <thread>
#include <condition_variable>


// channel

template <typename T>
class Channel {
private:
    std::queue<T> m_queue;
    std::mutex m_mutex;

    std::condition_variable m_cv_producer;
    std::condition_variable m_cv_consumer;

    size_t m_capacity {0};
    bool m_closed {false};

public:
    explicit Channel(size_t capacity) : m_capacity(capacity) {}

    bool send(T value) {
        std::unique_lock<std::mutex> lock(m_mutex);
        
        // 无缓冲 || 缓冲未满 || 触发关闭
        m_cv_producer.wait(lock, [this]() {
            return (m_capacity == 0 && m_queue.empty()) || m_queue.size() < m_capacity || m_closed;
        });

        if (m_closed) {
            return false;
        }

        m_queue.push(value);
        m_cv_consumer.notify_one();

        return true;
    }

    bool receive(T& value) {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_cv_consumer.wait(lock, [this]() {
            return !m_queue.empty() || m_closed;
        });

        if (m_closed && m_queue.empty()) {
            return false;
        }

        value = m_queue.front();
        m_queue.pop();
        m_cv_producer.notify_one();
        return true;
    }

    void close() {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_closed = true;
        m_cv_consumer.notify_all();
        m_cv_producer.notify_all();
    }
};


int main() {
    Channel<int> channel(10);

    auto producer = std::async(std::launch::async, [&]() {
        for (int i = 0; i < 100; i++) {
            channel.send(i);
            std::cout << "send " << i << std::endl;
        }
        channel.close();
    });

    auto consumer = std::async(std::launch::async, [&]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        int val;
        while (channel.receive(val)) {
            std::cout << "receive " << val << std::endl;
        }
    });

    // producer.wait();
    // consumer.wait();

    return 0;
}