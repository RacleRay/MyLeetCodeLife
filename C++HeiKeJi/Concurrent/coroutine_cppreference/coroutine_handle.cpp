#include <coroutine>
#include <iostream>
#include <optional>


template <std::movable T>
class Generator {
public:
    //=================================================================================
    // promise_type
    struct promise_type {
        std::optional<T> current_value;

        Generator<T> get_return_object() {
            return Generator{Handle::from_promise(*this)};
        }
        
        static std::suspend_always initial_suspend() noexcept { return {}; }
        static std::suspend_always final_suspend() noexcept { return {}; }

        std::suspend_always yield_value(T value) noexcept {
            current_value = std::move(value);
            return {};            
        }

        void await_transform() = delete;
        [[noreturn]] void unhandled_exception() { throw; }
    };

    using Handle = std::coroutine_handle<promise_type>;
    
    explicit Generator(const Handle coroutine) : m_coroutine(coroutine) {}

    //=================================================================================
    // constructor
    Generator() = default;
    ~Generator() {
        if (m_coroutine) {
            m_coroutine.destroy();
        }
    }

    Generator(const Generator&) = delete;
    Generator& operator=(const Generator&) = delete;

    Generator(Generator&& other) : m_coroutine(other.m_coroutine) {
        other.m_coroutine = {};
    }
    Generator& operator=(Generator&& other) {
        if (this != &other) {
            if (m_coroutine) {
                m_coroutine.destroy();
            }
            m_coroutine = other.m_coroutine;
            other.m_coroutine = {};
        }
        return *this;
    }
    
    //=================================================================================
    // for loop support
    class Iter {
    public:
        void operator++() {
            m_coroutine.resume();
        }
        const T& operator*() {
            return *m_coroutine.promise().current_value;
        }

        // out of range
        bool operator==(std::default_sentinel_t) const {
            return !m_coroutine || m_coroutine.done();
        }

        explicit Iter(const Handle coroutine) : m_coroutine(coroutine) {}

    private:
        Handle m_coroutine;
    };

    Iter begin() {
        if (m_coroutine) {
            m_coroutine.resume();
        }
        return Iter{m_coroutine};
    }

    std::default_sentinel_t end() { return {}; }

private:
    Handle m_coroutine;
};


template <std::integral T>
Generator<T> range(T first, T last) {
    while (first < last) {
        co_yield first;
        first++;
    }
}


int main() {
    for (const char i : range(65, 91)) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
    return 0;
}