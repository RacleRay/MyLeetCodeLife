/*************************************************************************
    > File Name: spinlock.cpp
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time: 
 ************************************************************************/
#include <iostream>
#include <atomic>
#include <thread>
#include <unistd.h>


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


class SpinLockE {
public:
    void lock() {
        for (int i = 0; flag.load(std::memory_order_relaxed) || flag.exchange(1, std::memory_order_acquire); ++i) {
            if (i == 8) {  // 多次尝试后放弃CPU
                lock_sleep();  // 比 sched_yield() 高效一些
                i = 0;
            }
        }
    }

    void unlock() {
        flag.store(0, std::memory_order_release);
    }

    void lock_sleep() {
    	static const timespec ns = {0, 1};  // 1 ns
        nanosleep(&ns, nullptr);
    }
    
private:
    std::atomic<unsigned int> flag{0};  
};