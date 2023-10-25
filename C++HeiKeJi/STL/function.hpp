#pragma once

#include <functional>
#include <memory>
#include <iostream>
#include <type_traits>


template <class FnSig>
class Function {
    // not Ret(Args...) function signature
    static_assert(!std::is_same_v<FnSig, FnSig>, "FnSig is not a function signature");
};

template <class Ret, class ...Args>
class Function<Ret(Args...)> {
private:
    struct FuncBase {
        // 类型擦除后的接口
        virtual Ret call(Args ...args) = 0;
        virtual ~FuncBase() = default;
    };

    // instantiate for different function signature
    template <class F>
    struct FuncImpl: FuncBase {
        FuncImpl(F f) : m_f(std::move(f)) {}

        virtual Ret call(Args ...args) override {
            // return m_f(std::forward<Args>(args)...);
            return std::invoke(m_f, std::forward<Args>(args)...);
        }
    
    private:
        F m_f;
    };

    std::shared_ptr<FuncBase> m_base;

public:
    Function() = default;

    template <class F, class = std::enable_if_t<std::is_invocable_r_v<Ret, F &, Args...>>>
    Function(F f) : m_base(std::make_unique<FuncImpl<F>>(std::move(f))) {}

    Ret operator()(Args ...args) const {
        if (!m_base) [[unlikely]] {
            throw std::runtime_error("Function is not initialized");
        }
        return m_base->call(std::forward<Args>(args)...);
    }
};