/*************************************************************************
    > File Name: memsingleton.cpp
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time:
 ************************************************************************/

#include <atomic>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>

// 利用智能指针解决释放问题
class SingleMemoryModel {
private:
  SingleMemoryModel() {}
  SingleMemoryModel(const SingleMemoryModel &) = delete;
  SingleMemoryModel &operator=(const SingleMemoryModel &) = delete;

public:
  ~SingleMemoryModel() {
    std::cout << "single auto delete success " << std::endl;
  }
  static std::shared_ptr<SingleMemoryModel> GetInst() {
    // synchronizes with construct operations.
    if (_b_init.load(std::memory_order_acquire)) {
      return single;
    }
    // 此处一定是在 _b_init.store 之后，也就是一定是没有执行构造时才会执行到此处
    s_mutex.lock();

    // 此时已经获得锁，也就是说，锁保证了同步，memory_order_relaxed
    // 只是检查_b_init.store是否执行
    if (single != nullptr) {
      s_mutex.unlock();
      return single;
    }
    // construct
    single = std::shared_ptr<SingleMemoryModel>(new SingleMemoryModel);
    // synchronizes
    _b_init.store(true, std::memory_order_release);
    s_mutex.unlock();
    return single;
  }

private:
  static std::shared_ptr<SingleMemoryModel> single;
  static std::mutex s_mutex;
  static std::atomic<bool> _b_init;
};

std::shared_ptr<SingleMemoryModel> SingleMemoryModel::single = nullptr;
std::mutex SingleMemoryModel::s_mutex;
std::atomic<bool> SingleMemoryModel::_b_init = false;

void TestSingleMemory() {
  std::thread t1([]() {
    std::cout << "thread t1 singleton address is 0x: "
              << SingleMemoryModel::GetInst() << std::endl;
  });

  std::thread t2([]() {
    std::cout << "thread t2 singleton address is 0x: "
              << SingleMemoryModel::GetInst() << std::endl;
  });

  t2.join();
  t1.join();
}

int main() {
  TestSingleMemory();

  return 0;
}
