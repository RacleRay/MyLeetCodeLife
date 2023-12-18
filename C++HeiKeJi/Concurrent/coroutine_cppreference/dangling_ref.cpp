#include <coroutine>
#include <iostream>

struct promise;

struct coroutine : std::coroutine_handle<promise>
{
    using promise_type = ::promise;
};


struct promise {
    coroutine get_return_object() {
        return {coroutine::from_promise(*this)};
    }

    std::suspend_always initial_suspend() noexcept {
        return {};
    }

    std::suspend_always final_suspend() noexcept {
        return {};
    }

    void return_void() {}

    void unhandled_exception() {}
};


struct S {
    int i;
    coroutine f() {
        std::cout << "S::f() : " << i << std::endl;
        co_return;
    }
};


void bad_ref() {
    coroutine h = S{0}.f();
    // S{0} had been destoryed
    h.resume();
    h.destroy();
}


coroutine bad_call() {
    S s{0};
    return s.f();  // s will be destoryed out of this scope
}


void bad_ref2() {
    coroutine h = [i = 0]() -> coroutine {
        std::cout << "Temp lambda call by capture: " << i << std::endl;
        co_return;
    }();  // (anonymous lambda type)::i will be destoryed with lambda
    h.resume();
    h.destroy();
}


void good_ref() {
    coroutine h = [](int i) -> coroutine {
        std::cout << "Temp lambda call by parameter: " << i << std::endl;
        co_return;
    }(0);
    h.resume();  // i was passed by value, so it won't be destoryed.
    h.destroy();
}


int main() {
    bad_ref();
    bad_ref2();

    coroutine h = bad_call();
    h.resume();
    h.destroy();

    good_ref();
    return 0;
}