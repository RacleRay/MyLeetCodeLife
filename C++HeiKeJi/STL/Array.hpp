#pragma once

#include <iterator>
#include <stdexcept>
#include <string>


#define _THROW_OUT_OF_RANGE(_i, _n)  { \
    throw std::runtime_error("Index out of range: " + std::to_string((_i)) + " >= " + std::to_string((_n))); \
}

#if defined(_MSC_VER)
#define _HEIKEJI_UNREACHABLE() __assume(0)
#elif defined(__clang__)
#define _HEIKEJI_UNREACHABLE() __builtin_unreachable()
#elif defined(__GNUC__)
#define _HEIKEJI_UNREACHABLE() __builtin_unreachable()
#else
#define _HEIKEJI_UNREACHABLE() do {} while (1)
#endif
// 为啥不是 while (1) ，这个是为了防止  while (1) 之后，如果使用者写了 {...} 的话，
// 就会导致死循环执行 {} 内的代码


template <class _Tp, size_t _N>
class Array {
public:
    /*
    using value_type = _Tp;
    using pointer = _Tp*;
    using const_pointer = _Tp const *;
    using reference = _Tp &;
    using const_reference = _Tp const &;
    using iterator = _Tp *;
    using const_iterator = _Tp const *;
    using reverse_iterator = _Tp *;
    using const_reverse_iterator = _Tp const *;
    */

    _Tp &operator[](size_t i) {
        return this->at(i);
    }

    _Tp const &operator[](size_t i) const {
        return this->at(i);
    }

    _Tp &at(size_t i) {
        if (i >= _N) [[__unlikely__]]
            _THROW_OUT_OF_RANGE(i, _N);
        return _m_elements[i];
    }

    _Tp const &at(size_t i) const {
        if (i >= _N) [[__unlikely__]]
            _THROW_OUT_OF_RANGE(i, _N);
        return _m_elements[i];
    }

    
    /*
        constexpr : 编译期可以取得 size 值
        static    : 不依赖于实例，可以使用 decay_t<decltype<var>> 的方式取得 N
    */
    static constexpr size_t size() noexcept {
        return _N;
    }

    static constexpr size_t max_size() noexcept {
        return _N;
    }

    static constexpr bool empty() noexcept {
        return false;
    }

    _Tp &front() noexcept {
        return _m_elements[0];
    }

    _Tp const &front() const noexcept {
        return _m_elements[0];
    }

    _Tp &back() noexcept {
        return _m_elements[_N - 1];
    }

    _Tp const &back() const noexcept {
        return _m_elements[_N - 1];
    }

    // 无异常赋值前提下，noexcept(true)
    // void fill(_Tp const &__val) noexcept(noexcept(std::declval(T &)() = std::declval<T()))
    void fill(const _Tp &value) noexcept(std::is_nothrow_copy_assignable_v<_Tp>) {
        for (size_t i = 0; i < _N; i++) {
            _m_elements[i] = value;
        }
    }

    void swap(Array &other) noexcept(std::is_nothrow_copy_assignable_v<_Tp>) {
        for (size_t i = 0; i < _N; i++) {
            std::swap(_m_elements[i], other._m_elements[i]);
        }
    }

    _Tp *data() noexcept {
        return _m_elements;
    }

    _Tp const *cdata() const noexcept {
        return _m_elements;
    }

    _Tp *begin() noexcept {
        return _m_elements;
    }

    _Tp *end() noexcept {
        return _m_elements + _N;
    }

    std::reverse_iterator<_Tp *> rbegin() noexcept {
        return std::reverse_iterator<_Tp *>(_m_elements);
    }

    std::reverse_iterator<_Tp *> rend() noexcept {
        return std::reverse_iterator<_Tp *>(_m_elements + _N);
    }

// private:  
// 如果是 private，那么就不能在外部访问了，那么
// ```
// template <class _Tp, class ..._Ts>
// Array(_Tp, _Ts...) -> Array<_Tp, 1 + sizeof...(_Ts)>;
// ```
// 那么
// auto a = Array{2, 1, 0};
// 不能成功编译

    _Tp _m_elements[_N];
};


template <class _Tp>
class Array<_Tp, 0> {
public:
    _Tp &operator[](size_t i) {
        _HEIKEJI_UNREACHABLE();
    }

    _Tp const &operator[](size_t i) const {
        _HEIKEJI_UNREACHABLE();
    }

    _Tp &at(size_t i) {
        _THROW_OUT_OF_RANGE(i, 0);
    }

    _Tp const &at(size_t i) const {
        _THROW_OUT_OF_RANGE(i, 0);
    }

    static constexpr size_t size() noexcept {
        return 0;
    }

    static constexpr size_t max_size() noexcept {
        return 0;
    }

    static constexpr bool empty() noexcept {
        return true;
    }

    _Tp &front() noexcept {
        _HEIKEJI_UNREACHABLE();
    }

    _Tp const &front() const noexcept {
        _HEIKEJI_UNREACHABLE();
    }

    _Tp &back() noexcept {
        _HEIKEJI_UNREACHABLE();
    }

    _Tp const &back() const noexcept {
        _HEIKEJI_UNREACHABLE();
    }

    // 无异常赋值前提下，noexcept(true)
    // void fill(_Tp const &__val) noexcept(noexcept(std::declval(T &)() = std::declval<T()))
    void fill(const _Tp &value) noexcept(std::is_nothrow_copy_assignable_v<_Tp>) {
        _HEIKEJI_UNREACHABLE();
    }

    void swap(Array &other) noexcept(std::is_nothrow_copy_assignable_v<_Tp>) {
        _HEIKEJI_UNREACHABLE();
    }

    _Tp *data() noexcept {
        _HEIKEJI_UNREACHABLE();
    }

    _Tp const *cdata() const noexcept {
        _HEIKEJI_UNREACHABLE();
    }

    _Tp *begin() noexcept {
        _HEIKEJI_UNREACHABLE();
    }

    _Tp *end() noexcept {
        _HEIKEJI_UNREACHABLE();
    }

    std::reverse_iterator<_Tp *> rbegin() noexcept {
        _HEIKEJI_UNREACHABLE();
    }

    std::reverse_iterator<_Tp *> rend() noexcept {
        _HEIKEJI_UNREACHABLE();
    }
};


// 首元素识别类型，容量需要 + 1，加上 _Tp
// 转换为 Array<_Tp, sizeof...(_Ts) + 1> 实例化模板
template <class _Tp, class ..._Ts>
Array(_Tp, _Ts...) -> Array<_Tp, 1 + sizeof...(_Ts)>;