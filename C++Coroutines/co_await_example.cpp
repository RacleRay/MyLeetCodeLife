/*************************************************************************
    > File Name: co_await_example.cpp
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time: 
 ************************************************************************/

#include <coroutine>
#include <iostream>


size_t level = 0;
std::string INDENT = "-";


class Trace {
public:
    Trace() {
        in_level();
    }

    ~Trace() {
        level -= 1;
    }

    void in_level() {
        level += 1;
        std::string res(INDENT);
        for (size_t i = 0; i < level; ++i) {
            res.append(INDENT);
        }
        std::cout << res;
    }
};


template <typename T>
struct sync {
    struct promise_type;
    using handle_type = std::coroutine_handle<promise_type>;
    handle_type coro;

    sync(handle_type h) : coro(h) {
        Trace t;
        std::cout << "Created a sync object" << std::endl;
    }

    sync(const sync&) = delete;

    sync(sync &&s) : coro(s.coro) {
        Trace t;
        std::cout << "Sync moved leaving behind a husk" << std::endl;
        s.coro = nullptr;
    }

    ~sync() {
        Trace t;
        std::cout << "Sync gone" << std::endl;
        if (coro) {
            coro.destroy();
        }
    }

    sync& operator=(const sync&) = delete;

    sync& operator=(sync &&s) {
        coro = s.coro;
        s.coro = nullptr;
        return *this;
    }

public:
    T get() {
        Trace t;
        std::cout << "return value ..." << std::endl;
        return coro.promise().value;
    }

public:
    struct promise_type {
        T value;

        promise_type() {
            Trace t;
            std::cout << "Promise created" << std::endl;
        }

        ~promise_type() {
            Trace t;
            std::cout << "Promise destroyed" << std::endl;
        }

        auto get_return_object() {
            Trace t;
            std::cout << "Send back a sync" << std::endl;
            // You have to this is a legal promise type
            return sync<T>{ handle_type::from_promise(*this) };
        }

        auto initial_suspend() {
            Trace t;
            std::cout << "Started the coroutine. " << std::endl;
            return std::suspend_never{};
        }

        auto return_value(T v) {
            Trace t;
            std::cout << "Got value: " << v << std::endl;
            value = v;
            return std::suspend_never{};
        }

        auto final_suspend() noexcept {
            Trace t;
            std::cout << "Finished the coroutine" << std::endl;
            return std::suspend_always{};
        }

        void unhandled_exception() {
            std::exit(1);
        }
    };
};


template <typename T>
struct lazy {
    struct promise_type;
    using handle_type = std::coroutine_handle<promise_type>;
    handle_type coro;

    lazy(handle_type h) : coro(h) {
        Trace t;
        std::cout << "Created a lazy object" << std::endl;
    }

    lazy(const lazy&) = delete;

    lazy(lazy &&l) : coro(l.coro) {
        Trace t;
        std::cout << "Lazy moved leaving behind a husk" << std::endl;
        l.coro = nullptr;
    }

    ~lazy() {
        Trace t;
        std::cout << "Lazy gone" << std::endl;
        if (coro) {
            coro.destroy();
        }
    }

    lazy& operator=(const lazy&) = delete;
    lazy& operator=(lazy &&l) {
        coro = l.coro;
        l.coro = nullptr;
        return *this;
    }

public:
    T get() {
        Trace t;
        std::cout << "return value ..." << std::endl;
        return coro.promise().value;
    }

    bool await_ready() {
        const auto ready = this->coro.done();
        Trace t;
        std::cout << "Await " << (ready ? "is ready" : "isn`t ready") << std::endl;
        return this->coro.done();
    }

    void await_suspend(std::coroutine_handle<> awaiting) {
        {
            Trace t;
            std::cout << "About to resume the lazy" << std::endl;
            this->coro.resume();
        }

        Trace t;
        std::cout << "About to resume the awaiter" << std::endl;
        awaiting.resume();
    }

    auto await_resume() {
        const auto r = this->coro.promise().value;
        Trace t;
        std::cout << "Await value is returned: " << r << std::endl;
        return r;
    }

public:
    struct promise_type {
        T value;

        promise_type() {
            Trace t;
            std::cout << "Promise created" << std::endl;
        }

        ~promise_type() {
            Trace t;
            std::cout << "Promise destroyed" << std::endl;
        }

        auto get_return_object() {
            Trace t;
            std::cout << "Send back a lazy" << std::endl;
            // You have to this is a legal promise type
            return lazy<T>{ handle_type::from_promise(*this) };
        }

        auto initial_suspend() {
            Trace t;
            std::cout << "Started the coroutine. " << std::endl;
            return std::suspend_always{};
        }

        auto return_value(T v) {
            Trace t;
            std::cout << "Got value: " << v << std::endl;
            value = v;
            return std::suspend_never{};
        }

        auto final_suspend() noexcept {
            Trace t;
            std::cout << "Finished the coroutine" << std::endl;
            return std::suspend_always{};
        }

        void unhandled_exception() {
            std::exit(1);
        }
    };
};


lazy<std::string> read_data() {
    Trace t;
    
    std::cout << "Read data ..." << std::endl;
    co_return "123456";
}


lazy<std::string> write_data() {
    Trace t;
    std::cout << "Write data ..." << std::endl;
    co_return "654321";
}


sync<int> reply() {
    std::cout << "Started await_answer" << std::endl;
    auto a = co_await read_data();
    std::cout << "Data we got is " << a << std::endl;
    auto v = co_await write_data();
    std::cout << "Write result is " << v << std::endl;
    co_return 42;
}


int main() {
    std::cout << "Started main" << std::endl;
    auto a = reply();
    return a.get();
}
