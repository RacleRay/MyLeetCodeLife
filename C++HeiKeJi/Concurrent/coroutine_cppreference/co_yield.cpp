#include <coroutine>
#include <exception>
#include <iostream>
#include <memory>

template <typename T>
struct Generator {
    // 定义一个 promise_type 类型，用于生成 handle_type
    struct promise_type;
    using handle_type = std::coroutine_handle<promise_type>;
    struct promise_type {
        T value;  // 在 promise 中暂存了值
        std::exception_ptr exception;

        Generator get_return_object() {
            return Generator(handle_type::from_promise(*this));
        }

        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void unhandled_exception() { exception = std::current_exception(); }

        template <std::convertible_to<T> From>
        std::suspend_always yield_value(From&& from) {
            value = std::forward<From>(from);
            return {};
        }

        void return_void() {}
    };

    // 构造函数传入 handle_type，用于生成 Generator 对象
    handle_type h;
    Generator(handle_type hdl) : h(hdl) {}
    ~Generator() { h.destroy(); }

    explicit operator bool() {
        fill();  // 调用 fill() 方法，填充 promise 中的值和异常对象；如果过没有使用 operator()，则不会重复执行协程
        return !h.done();
    }

    T operator()() {
        fill();
        m_full = false;
        return std::move(h.promise().value);  // 返回 promise 中暂存的值
    }

private:
    bool m_full = false;

    void fill() {
        if (!m_full) {
            h();  // 调用 handle_type::operator()，触发协程执行
            // handle 中存储的 promise 对象，暂存了当前的目标变量值拷贝和程序异常对象
            if (h.promise().exception) {
                std::rethrow_exception(h.promise().exception);
            }
            m_full = true;
        }
    }

};


Generator<uint64_t>
fibonacci_sequence(unsigned n) {
    if (n == 0) {
        co_return ;
    }
    if (n > 94) {
        throw std::runtime_error("n too large, number will overflow");
    }

    co_yield 0;
    if (n == 1) {
        co_return;
    }
    
    co_yield 1;
    if (n == 2) {
        co_return;
    }

    uint64_t a = 0;
    uint64_t b = 1;

    for (unsigned i = 2; i < n; ++i) {
        uint64_t s = a + b;
        co_yield s;
        a = b;
        b = s;
    }
}


int main() {
    try {
        auto gen = fibonacci_sequence(1);
        for (int j = 0; gen; ++j) {
            std::cout << "fibonacci[" << j << "] = " << gen() << '\n';
        }
    } catch (const std::exception& e) {
        std::cerr << "exception: " << e.what() << '\n';
    } catch (...) {
        std::cerr << "unknown exception\n";
    }

    return 0;
}