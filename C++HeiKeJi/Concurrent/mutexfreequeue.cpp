#include <atomic>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>

/**
 *  compare_exchange_strong:
template <typename T>
bool atomic<T>::compare_exchange_strong(T &expected, T desired) {
    std::lock_guard<std::mutex> guard(m_lock);
    if (m_val == expected)
        return m_val = desired, true;
    else
        return expected = m_val, false;
}

 *  compare_exchange_weak
不保证 atomic 变量和 expected 值相等时，一定返回 true，不保证 m_val = desired,
true; 的执行

 */

#define ATOM_CHECK_BEGIN()                                                     \
  bool atom_expected = false;                                                  \
  bool atom_desired = true;                                                    \
                                                                               \
  do {                                                                         \
    atom_expected = false;                                                     \
    atom_desired = true;                                                       \
  } while (!m_using_atom.compare_exchange_strong(atom_expected, atom_desired));

#define ATOM_CHECK_END()                                                       \
  do {                                                                         \
    atom_expected = true;                                                      \
    atom_desired = false;                                                      \
  } while (!m_using_atom.compare_exchange_strong(atom_expected, atom_desired));


// ===============================================================================
// 单一原子变量
template <typename T, size_t Cap>
class QueueWithoutMutex : private std::allocator<T> {
public:
  QueueWithoutMutex() : m_data(std::allocator<T>::allocate(m_size)) {}

  QueueWithoutMutex(const QueueWithoutMutex &) = default;
  QueueWithoutMutex &operator=(const QueueWithoutMutex &) = delete;
  QueueWithoutMutex(QueueWithoutMutex &&) = delete;
  QueueWithoutMutex &operator=(QueueWithoutMutex &&) = delete;

  ~QueueWithoutMutex() {
    ATOM_CHECK_BEGIN();
    // m_using_atom 为 false 时才会退出循环，并置为 true

    while (!empty()) {
      std::allocator<T>::destroy(m_data + m_head);
      m_head = (m_head + 1) % m_size;
    }
    std::allocator<T>::deallocate(m_data, m_size);

    ATOM_CHECK_END();
    // m_using_atom 为 true 时才会退出循环，并置为 false
  }

  template <typename... Args> bool emplace(Args &&...args) {
    ATOM_CHECK_BEGIN();
    // m_using_atom 为 false 时才会退出循环，并置为 true

    if (full()) {
      std::cout << "queue is full" << std::endl;
      ATOM_CHECK_END();
      return false;
    }
    std::allocator<T>::construct(m_data + m_tail, std::forward<Args>(args)...);
    m_tail = (m_tail + 1) % m_size;

    ATOM_CHECK_END();
    // m_using_atom 为 true 时才会退出循环，并置为 false
    return true;
  }

  bool push(const T &val) {
    std::cout << "push lvalue " << val << std::endl;
    return emplace(val);
  }

  bool push(T &&val) {
    std::cout << "push rvalue " << val << std::endl;
    return emplace(std::move(val));
  }

  bool pop(T &val) {
    ATOM_CHECK_BEGIN();

    if (empty()) {
      std::cout << "queue is empty" << std::endl;
      ATOM_CHECK_END();
      return false;
    }
    val = std::move(m_data[m_head]);
    m_head = (m_head + 1) % m_size;

    ATOM_CHECK_END();
    return true;
  }

  bool empty() const noexcept { return m_head == m_tail; }

  bool full() const noexcept { return (m_tail + 1) % m_size == m_head; }

private:
  size_t m_size{Cap + 1};
  T *m_data;

  // std::mutex m_mtx;
  std::atomic<bool> m_using_atom{false};

  size_t m_head{0};
  size_t m_tail{0};
};

void test_QueueWithoutMutex() {
  QueueWithoutMutex<int, 3> queue_wm;
  for (int i = 0; i < 4; i++) {
    int mc1(i);
    auto res = queue_wm.push(mc1);
    if (!res) {
      break;
    }
  }

  for (int i = 0; i < 4; i++) {
    int mc1;
    auto res = queue_wm.pop(mc1);
    if (!res) {
      break;
    }

    std::cout << "pop success, " << mc1 << std::endl;
  }

  for (int i = 0; i < 4; i++) {
    int mc1(i);
    auto res = queue_wm.push(mc1);
    if (!res) {
      break;
    }
  }

  for (int i = 0; i < 4; i++) {
    int mc1;
    auto res = queue_wm.pop(mc1);
    if (!res) {
      break;
    }

    std::cout << "pop success, " << mc1 << std::endl;
  }
}


// ===============================================================================
// push pop 解耦，而不是单一原子变量
template <typename T, size_t Cap>
class QueueWithoutMutexDecpl : private std::allocator<T> {
public:
  QueueWithoutMutexDecpl() : m_data(std::allocator<T>::allocate(m_size)) {}

  QueueWithoutMutexDecpl(const QueueWithoutMutexDecpl &) = default;
  QueueWithoutMutexDecpl &operator=(const QueueWithoutMutexDecpl &) = delete;
  QueueWithoutMutexDecpl(QueueWithoutMutexDecpl &&) = delete;
  QueueWithoutMutexDecpl &operator=(QueueWithoutMutexDecpl &&) = delete;

  ~QueueWithoutMutexDecpl() {
    while (!empty()) {
      std::allocator<T>::destroy(m_data + m_head);
      m_head = (m_head + 1) % m_size;
    }
    std::allocator<T>::deallocate(m_data, m_size);
  }

  template <typename... Args> bool emplace(Args &&...args) {
    size_t tail;
    do {
        tail = m_tail.load();
        if ((tail + 1) % m_size == m_head.load()) {
            std::cout << "queue is full" << std::endl;
            return false;
        }
    } while (!m_tail.compare_exchange_strong(tail, (tail + 1) % m_size));
    // synchronize 
    // tail == m_tail, 也即期间 m_tail 没有被修改过
    // 原子地将 tail + 1

    std::allocator<T>::construct(&m_data[tail], std::forward<Args>(args)...);

    size_t tail_new;
    do {
        tail_new = tail;
    } while (m_tail_update.compare_exchange_strong(tail_new, (tail_new + 1) % m_size));
    // synchronize 
    // m_tail_update 指向下一个待插入位置
    // m_tail 指向当前需要插入的位置

    return true;
  }

  bool push(const T &val) {
    std::cout << "push lvalue " << val << std::endl;
    return emplace(val);
  }

  bool push(T &&val) {
    std::cout << "push rvalue " << val << std::endl;
    return emplace(std::move(val));
  }

  bool pop(T &val) {
    size_t head;
    do {
        head = m_head.load();
        if (head == m_tail.load()) {
            std::cout << "queue is empty" << std::endl;
            return false;
        }

        if (head == m_tail_update.load()) {
            std::cout << "after construct, before tail update" << std::endl;
            return false;
        }

        val = m_data[head];
    } while (!m_head.compare_exchange_strong(head, (head + 1) % m_size));
    // m_head != head 会持续synchronize, head 会被赋值为 m_head
    // 同步完成后，head + 1 

    // std::cout << "pop success, " << val << std::endl;
    return true;
  }

  bool empty() const noexcept { return m_head == m_tail; }

  bool full() const noexcept { 
    return m_head == (m_tail + 1) % m_size;
  }

private:
  size_t m_size{Cap + 1};
  T *m_data;

  // std::mutex m_mtx;
  // std::atomic<bool> m_using_atom{false};

  // size_t m_tail{0};
  // size_t m_head{0};

  std::atomic<size_t> m_head{0};
  std::atomic<size_t> m_tail{0};
  std::atomic<size_t> m_tail_update{0};
};


void test_QueueWithoutMutexDecpl() {
  QueueWithoutMutexDecpl<int, 3> queue_wm_opti;
  for (int i = 0; i < 4; i++) {
    int mc1(i);
    auto res = queue_wm_opti.push(mc1);
    if (!res) {
      break;
    }
  }

  for (int i = 0; i < 4; i++) {
    int mc1;
    auto res = queue_wm_opti.pop(mc1);
    if (!res) {
      break;
    }

    std::cout << "pop success, " << mc1 << std::endl;
  }

  for (int i = 0; i < 4; i++) {
    int mc1(i);
    auto res = queue_wm_opti.push(mc1);
    if (!res) {
      break;
    }
  }

  for (int i = 0; i < 4; i++) {
    int mc1;
    auto res = queue_wm_opti.pop(mc1);
    if (!res) {
      break;
    }

    std::cout << "pop success, " << mc1 << std::endl;
  }
}


// ============================================================================
// acquire and release 优化
// 原子操作默认采用的是memory_order_seq_cst内存顺序，性能上不是最优的，我们可以用acquire和release的内存顺序实现同步的效果
// 期望的条件匹配时采用memory_order_release, 期望的条件不匹配时memory_order_relaxed，
// 条件不配时，因为会再次进入循环检查，所以 relaxed 没问题
// 
template <typename T, size_t Cap>
class QueueWithoutMutexDecplOpt : private std::allocator<T> {
public:
  QueueWithoutMutexDecplOpt() : m_data(std::allocator<T>::allocate(m_size)) {}

  QueueWithoutMutexDecplOpt(const QueueWithoutMutexDecplOpt &) = default;
  QueueWithoutMutexDecplOpt &operator=(const QueueWithoutMutexDecplOpt &) = delete;
  QueueWithoutMutexDecplOpt(QueueWithoutMutexDecplOpt &&) = delete;
  QueueWithoutMutexDecplOpt &operator=(QueueWithoutMutexDecplOpt &&) = delete;

  ~QueueWithoutMutexDecplOpt() {
    while (!empty()) {
      std::allocator<T>::destroy(m_data + m_head);
      m_head = (m_head + 1) % m_size;
    }
    std::allocator<T>::deallocate(m_data, m_size);
  }

  template <typename... Args> bool emplace(Args &&...args) {
    size_t tail;
    do {
        tail = m_tail.load(std::memory_order_relaxed);
        if ((tail + 1) % m_size == m_head.load(std::memory_order_acquire)) {
            std::cout << "queue is full" << std::endl;
            return false;
        }
    } while (!m_tail.compare_exchange_strong(tail, (tail + 1) % m_size,
        std::memory_order_release, std::memory_order_relaxed));
    // synchronize 
    // tail == m_tail, 也即期间 m_tail 没有被修改过
    // 原子地将 tail + 1

    std::allocator<T>::construct(&m_data[tail], std::forward<Args>(args)...);

    size_t tail_new;
    do {
        tail_new = tail;
    } while (m_tail_update.compare_exchange_strong(tail_new, (tail_new + 1) % m_size, 
        std::memory_order_release, std::memory_order_relaxed));
    // synchronize 
    // m_tail_update 指向下一个待插入位置
    // m_tail 指向当前需要插入的位置

    return true;
  }

  bool push(const T &val) {
    std::cout << "push lvalue " << val << std::endl;
    return emplace(val);
  }

  bool push(T &&val) {
    std::cout << "push rvalue " << val << std::endl;
    return emplace(std::move(val));
  }

  bool pop(T &val) {
    size_t head;
    do {
        head = m_head.load(std::memory_order_relaxed);
        if (head == m_tail.load(std::memory_order_acquire)) {
            std::cout << "queue is empty" << std::endl;
            return false;
        }

        // 保证 pop 的位置是一定是 push 后的结果
        if (head == m_tail_update.load(std::memory_order_acquire)) {
            std::cout << "after construct, before tail update" << std::endl;
            return false;
        }

        val = m_data[head];
    } while (!m_head.compare_exchange_strong(head, (head + 1) % m_size, 
        std::memory_order_release, std::memory_order_relaxed));
    // m_head != head 会持续synchronize, head 会被赋值为 m_head
    // 同步完成后，head + 1 

    // std::cout << "pop success, " << val << std::endl;
    return true;
  }

  bool empty() const noexcept { return m_head == m_tail; }

  bool full() const noexcept { 
    return m_head == (m_tail + 1) % m_size;
  }

private:
  size_t m_size{Cap + 1};
  T *m_data;

  // std::mutex m_mtx;
  // std::atomic<bool> m_using_atom{false};

  // size_t m_tail{0};
  // size_t m_head{0};

  std::atomic<size_t> m_head{0};
  std::atomic<size_t> m_tail{0};
  std::atomic<size_t> m_tail_update{0};
};


void test_QueueWithoutMutexDecplOpt() {
  QueueWithoutMutexDecplOpt<int, 3> queue_wm_opti;
  for (int i = 0; i < 4; i++) {
    int mc1(i);
    auto res = queue_wm_opti.push(mc1);
    if (!res) {
      break;
    }
  }

  for (int i = 0; i < 4; i++) {
    int mc1;
    auto res = queue_wm_opti.pop(mc1);
    if (!res) {
      break;
    }

    std::cout << "pop success, " << mc1 << std::endl;
  }

  for (int i = 0; i < 4; i++) {
    int mc1(i);
    auto res = queue_wm_opti.push(mc1);
    if (!res) {
      break;
    }
  }

  for (int i = 0; i < 4; i++) {
    int mc1;
    auto res = queue_wm_opti.pop(mc1);
    if (!res) {
      break;
    }

    std::cout << "pop success, " << mc1 << std::endl;
  }
}


int main() { 
    test_QueueWithoutMutex();
    std::cout << "----------------------------------------------" << std::endl;
    test_QueueWithoutMutexDecpl();
    std::cout << "----------------------------------------------" << std::endl;
    test_QueueWithoutMutexDecplOpt();
    return 0;
}