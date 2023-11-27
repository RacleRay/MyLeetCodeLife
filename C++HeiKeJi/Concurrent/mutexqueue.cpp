#include <atomic>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>


template <typename T, size_t Cap>
class QueueWithMutex: private std::allocator<T> {
public:

    QueueWithMutex(): m_data(std::allocator<T>::allocate(m_size)) {}
    
    QueueWithMutex(const QueueWithMutex&) = default;
    QueueWithMutex& operator=(const QueueWithMutex&) = delete;
    QueueWithMutex(QueueWithMutex&&) = delete;
    QueueWithMutex& operator=(QueueWithMutex&&) = delete;

    ~QueueWithMutex() {
        std::lock_guard<std::mutex> lock(m_mtx);
        while (!empty()) {
            std::allocator<T>::destroy(m_data + m_head);
            m_head = (m_head + 1) % m_size;
        }
        std::allocator<T>::deallocate(m_data, m_size);
    }

    template<typename ...Args>
    bool emplace(Args&& ...args) {
        std::lock_guard<std::mutex> lock(m_mtx);
        if (full()) {
            std::cout << "queue is full" << std::endl;
            return false;
        }
        std::allocator<T>::construct(m_data + m_tail, std::forward<Args>(args)...);
        m_tail = (m_tail + 1) % m_size;
        return true;
    }

    bool push(const T& val) {
        std::cout << "push lvalue " << val << std::endl;
        return emplace(val);
    }

    bool push(T&& val) {
        std::cout << "push rvalue " << val << std::endl;
        return emplace(std::move(val));
    }

    bool pop(T& val) {
        std::lock_guard<std::mutex> lock(m_mtx);
        if (empty()) {
            std::cout << "queue is empty" << std::endl;
            return false;
        }
        val = std::move(m_data[m_head]);
        m_head = (m_head + 1) % m_size;
        return true;
    }

    bool empty() const noexcept {
        return m_head == m_tail;
    }

    bool full() const noexcept {
        return (m_tail + 1) % m_size  == m_head;
    }

private:
    size_t m_size{Cap + 1};
    T* m_data;
    
    std::mutex m_mtx;

    size_t m_head{0};
    size_t m_tail{0};
};



void test() {
    QueueWithMutex<int, 5> q;
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    q.push(5);
    q.push(6);
    
    int tmp = 0;
    q.pop(tmp);

}


int main() {
    test();
}