/*************************************************************************
    > File Name: spinlock.cpp
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time: 
 ************************************************************************/
#include <iostream>
#include <atomic>
#include <thread>


class SpinLock {
public:
    void lock() {
        // 线程2循环检测一直为true
        while (flag.test_and_set(std::memory_order_acquire));
    }

    void unlock() {
        flag.clear(std::memory_order_release);
    }

private:
    std::atomic_flag flag = ATOMIC_FLAG_INIT;
};
