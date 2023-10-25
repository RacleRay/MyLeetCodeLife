#pragma once

#include <cstdio>
#include <utility>
#include <type_traits>

/** 
    note : delete nullptr; free(nullptr); 是可以的
           fclose(nullptr); 是不行的，需要检查是否是空指针

*/

// ======================================
template <class T>
struct DefaultDeleter {
    void operator()(T *ptr) const {
        delete ptr;
    }
};


template <class T>
struct DefaultDeleter<T[]> {
    void operator()(T *ptr) const {
        delete[] ptr;
    }
};


template <>
struct DefaultDeleter<FILE> {
    void operator()(FILE *ptr) const {
        fclose(ptr);
    }
};
// ======================================

template <class T, class U>
T exchange(T &dst, U &&src) {  // universal reference, in case std::nullptr_t
    T tmp = std::move(dst);  // recovery current dst resource
    dst = std::forward<U>(src);
    return tmp;
}


template <class T, class Deleter = DefaultDeleter<T>>
struct UniquePtr {
private:
    T *m_ptr;

    template<class U, class UDeleter>
    friend struct UniquePtr;

public:
    // default constructor
    UniquePtr(std::nullptr_t = nullptr) : m_ptr(nullptr) {}

    explicit UniquePtr(T *ptr): m_ptr(ptr) {}

    // 保证U是可以由T类型指针指向的，即U为T的子类时
    // template <class U, class UDeleter> requires (std::convertible_to<U*, T*>) // C++20
    template <class U, class UDeleter, class = std::enable_if_t<std::is_convertible_v<U*, T*>>>
    UniquePtr(UniquePtr<U, UDeleter> &&other) {
        m_ptr = exchange(other.m_ptr, nullptr);
    }

    ~UniquePtr() {
        if (m_ptr) {
            Deleter{}(m_ptr);
        }
    }

    // 拷贝构造和赋值
    UniquePtr(UniquePtr const &other) = delete;
    UniquePtr& operator=(UniquePtr const &other) = delete;

    // 移动构造与赋值
    UniquePtr(UniquePtr &&other) {
        m_ptr = exchange(other.m_ptr, nullptr);
    }
    UniquePtr& operator=(UniquePtr &&other) {
        if (this == &other) [[unlikely]] {
            return *this;
        }

        // free current resource
        if (m_ptr) {
            Deleter{}(m_ptr);
        }
        // get new resource, and deal with dangling pointer
        m_ptr = exchange(other.m_ptr, nullptr);
        return *this;
    }

    T* get() const {
        return exchange(m_ptr, nullptr);
    }

    // if passing p, reset to it
    void reset(T* p = nullptr) {
        if (m_ptr) {
            Deleter{}(m_ptr);
        }
        m_ptr = p;
    }

    T& operator*() const {
        return *m_ptr;
    }

    T* operator->() const {
        return m_ptr;
    }
};


// 偏特化继承非特化版本实现
// 偏特化不能使用默认类型
template <class T, class Deleter>
struct UniquePtr<T[], Deleter> : UniquePtr<T, Deleter> {};

template <class T, class ...Args>
UniquePtr<T> makeUnique(Args&& ...args) {
    return UniquePtr<T> (new T(std::forward<Args>(args)...));
}

template <class T>
UniquePtr<T> makeUniqueForOverwrite() {
    // 不加 T()，初始化的值是随机的。不进行0初始化，效率会高一点
    return UniquePtr<T> (new T);  
}