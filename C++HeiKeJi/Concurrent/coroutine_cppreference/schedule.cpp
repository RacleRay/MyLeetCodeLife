#include <coroutine>
#include <chrono>
#include <future>
#include <iostream>
#include <thread>

using namespace std;


struct Task {
    struct promise_type;
    using handle_type = std::coroutine_handle<promise_type>;

    handle_type h;  // 协程的 handle
    std::future<void> fut;

    //=================================================================================
    // promise
    struct promise_type {
        int result;
        coroutine_handle<> h_next = nullptr;  // 调度的下一个协程

        Task get_return_object() {
            return Task{ handle_type::from_promise(*this) };
        }

        suspend_always initial_suspend() { return {};};

        auto final_suspend() noexcept {
            // 被 await 后，如果 h_next 不为空，则返回 h_next(调度到指定协程)，否则返回 std::noop_coroutine() (调度到协程的调用者)
            struct next_awaiter {  // as a promise
                promise_type* self;

                bool await_ready() noexcept { return false; }   // will suspend
                void await_resume() noexcept {};

                coroutine_handle<> await_suspend(coroutine_handle<promise_type> hdl) noexcept {
                    if (hdl.promise().h_next) {
                        return hdl.promise().h_next;   // 返回 h_next ，即调度的到下一个协程
                    } else {
                        return std::noop_coroutine();
                    }
                }
            };
            return next_awaiter{ this };
        }

        // called at co_return
        void return_value(int i) { result = i; }

        void unhandled_exception() {}
    };

    //=================================================================================
    // awaiter definition
    bool await_ready() { return false; }   // go to await_suspend
    // co_await will call await_suspend
    void await_suspend(handle_type hdl) {
        h.promise().h_next = hdl;  // 设置下一个协程(consume)
        // 另开线程执行 producer 协程 resume() , 此时异步地开始执行 produce() 函数
        fut = std::async([this]() { h.resume(); });
    }
    int await_resume() { return h.promise().result; }
};


// 协程 producer
Task produce() {
    // producer 协程 resume() ，从这里开始执行
    int val = 1111;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    cout << std::this_thread::get_id() << " produce: " << val << endl;
    co_return val;  // promise::return_value(int)
    // final_suspend 返回 consumer 的 coroutine_handle，即调度到 consumer 协程
    // 注意，此时 producer 协程还存在，同时，当前运行在 async 线程中
}


// 协程 consumer
Task consume(Task& fut) {
    cout << std::this_thread::get_id() << " consume: waiting " << endl;
    // 这里的 co_await 的是 producer (fut) ，传入 producer::await_suspend 的是 consumer 的 coroutine_handle 
    // 从 producer::await_suspend 开始执行
    int val = co_await fut;
    // 从 producer::final_suspend 执行结束后，调度到 consumer 协程，从此处开始执行
    // 在此之前，由 producer::await_resume 返回的结果，保存到 val
    // ！！！注意，此时 consumer 协程运行在 async 线程中
    cout << std::this_thread::get_id() << " consume: " << val << endl;
    co_return 0;  // promise::return_value(int)
    // 协程结束执行，即 async 线程结束
}


int main() {
    // 初始化协程
    auto prod = produce();
    auto cons = consume(prod);

    // consumer 协程 ，从 co_await 开始执行
    cons.h.resume();
    
    // 等待协程 consumer 协程执行完毕，但是当前程序不会阻塞，而是忙等待
    while (!cons.h.done()) {
        cout << std::this_thread::get_id() << " main: waiting " << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    cout << std::this_thread::get_id() << " main: done" << endl;

    return 0;  // 主线程结束，协程析构
}