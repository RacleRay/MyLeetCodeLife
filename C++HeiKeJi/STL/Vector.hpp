#pragma once

#include <cstdio>
#include <cstring>
#include <iostream>
#include <limits>
#include <string>
#include <stdexcept>
#include <utility>


template <class T, class Alloc=std::allocator<T>>
struct Vector {
    using value_type = T;
    using allocator_type = Alloc;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using pointer = T *;
    using const_pointer = T const *;
    using reference = T &;
    using const_reference = T const &;
    using iterator = T *;
    using const_iterator = T const *;
    using reverse_iterator = std::reverse_iterator<T *>;
    using const_reverse_iterator = std::reverse_iterator<T const *>;

    T *m_data;
    size_t m_size;
    size_t m_capacity;
    // 空基类优化，本来为空，会分配1字节，然后会扩展为8字节
    // 但是优化后，不需要有独一无二的地址，不会扩展为8字节
    [[no_unique_address]] Alloc m_alloc;

    Vector() noexcept: m_data(nullptr), m_size(0), m_capacity(0) {}

    Vector(std::initializer_list<T> list, Alloc const& alloc=Alloc())
    : Vector(list.begin(), list.end(), alloc) {};

    template<std::random_access_iterator InputIt>
    Vector(InputIt first, InputIt last, Alloc const& alloc=Alloc()): m_alloc(alloc){
        size_t n = last - first;
        m_data = m_alloc.allocate(n);
        m_capacity = m_size = n;
        for (size_t i = 0; i < n; ++i) {
            std::construct_at(&m_data[i], *first);
            ++first;
        }
    }

    explicit Vector(size_t n, Alloc const& alloc=Alloc()): m_alloc(alloc) {
        m_data = m_alloc.allocate(n);
        m_capacity = m_size = n;
        for (size_t i = 0; i < n; ++i) {
            std::construct_at(&m_data[i]);
        }
    }

    Vector(size_t n, T const& val, Alloc const& alloc=Alloc()): m_alloc(alloc) {
        m_data = m_alloc.allocate(n);
        m_capacity = m_size = n;
        for (size_t i = 0; i < n; ++i) {
            std::construct_at(&m_data[i], val);
        }
    }

    Vector(Vector const& other): m_alloc(other.m_alloc) {
        m_capacity = m_size = other.m_size;
        if (m_size == 0) {
            m_data = nullptr;
        } else {
            m_data = m_alloc.allocate(m_size);
            for (size_t i = 0; i < m_size; ++i) {
                std::construct_at(&m_data[i], std::as_const(other.m_data[i]));
            }
        }
    }

    Vector(Vector const &other, Alloc const &alloc) : m_alloc(alloc) {
        m_capacity = m_size = other.m_size;
        if(m_size == 0) {
            m_data = nullptr;
        } else {
            m_data = m_alloc.allocate(m_size);
            for (size_t i = 0; i < m_size; ++i) {
                std::construct_at(&m_data[i], std::as_const(other.m_data[i]));
            }
        }
    }

    Vector& operator=(Vector const& other) {
        if (this == &other) [[unlikely]] {
            return *this;
        }
        reserve(other.m_size);
        m_size = other.m_size;

        for (size_t i = 0; i < m_size; ++i) {
            std::construct_at(&m_data[i], std::as_const(other.m_data[i]));
        }

        return *this;
    }

    Vector(Vector&& other) noexcept: m_alloc(std::move(other.m_alloc)) {
        m_data = other.m_data;
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        other.m_data = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }

    Vector(Vector &&other, Alloc const &alloc) noexcept : m_alloc(alloc) {
        m_data = other.m_data;
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        other.m_data = nullptr;
        other.m_size = 0;
        other.m_cap = 0;
    }

    Vector& operator=(Vector&& other) noexcept {
        if (this == &other) [[unlikely]] { return *this; }

        for (size_t i = 0; i < m_size; ++i) {
            std::destroy_at(&m_data[i]);
        }

        if (m_capacity != 0) {
            m_alloc.deallocate(m_data, m_capacity);
        }

        m_data = other.m_data;
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        other.m_data = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;

        return *this;
    }

    ~Vector() noexcept {
        for (size_t i = 0; i < m_size; ++i) {
            std::destroy_at(&m_data[i]);
        }
        if (m_capacity != 0) {
            m_alloc.deallocate(m_data, m_capacity);
        }
    }

    void swap(Vector& other) noexcept {
        std::swap(m_data, other.m_data);
        std::swap(m_size, other.m_size);
        std::swap(m_capacity, other.m_capacity);
        std::swap(m_alloc, other.m_alloc);
    }

    void clear() noexcept {
        for (size_t i = 0; i < m_size; ++i) {
            std::destroy_at(&m_data[i]);
        }
        m_size = 0;
    }

    // 修改 m_capacity
    void reserve(size_t n) {
        if (n <= m_capacity) return;

        n = std::max(n, m_capacity * 2);

        auto old_data = m_data;
        size_t old_capacity = m_capacity;

        if (n == 0) {
            m_data = nullptr;
            m_capacity = 0;
        } else {
            m_data = m_alloc.allocate(n);
            m_capacity = n;
        }

        if (old_capacity != 0) {
            for (size_t i = 0; i < m_size; ++i) {
                std::construct_at(&m_data[i], std::move_if_noexcept(old_data[i]));
            }
            for (size_t i = 0; i < old_capacity; ++i) {
                std::destroy_at(&old_data[i]);
            }
            m_alloc.deallocate(old_data, old_capacity);
        }
    }

    // 修改 m_size
    void resize(size_t n) {
        if (n < m_size) {
            for (size_t i = n; i < m_size; ++i) {
                std::destroy_at(&m_data[i]);
            }
            m_size = n;
        } else if (n > m_size) {
            reserve(n);
            for (size_t i = m_size; i < n; ++i) {
                std::construct_at(&m_data[i]);
            }
        }
        m_size = n;
    }

    void resize(size_t n, T const& val) {
        if (n < m_size) {
            for (size_t i = n; i != m_size; i++) {
                std::destroy_at(&m_data[i]);
            }
            m_size = n;
        } else if (n > m_size) {
            reserve(n);
            for (size_t i = m_size; i != n; i++) {
                std::construct_at(&m_data[i], val);
            }
        }
        m_size = n;
    }

    // 修改 m_capacity = m_size
    void shrink_to_fit() noexcept {
        auto old_data = m_data;
        size_t old_capacity = m_capacity;

        m_capacity = m_size;
        if (m_size == 0) {
            m_data = nullptr;
        } else {
            m_data = m_alloc.allocate(m_size);
        }

        if (old_capacity == 0) [[unlikely]] return;
        for (size_t i = 0; i < m_size; ++i) {
            std::construct_at(&m_data[i], std::move_if_noexcept(old_data[i]));
            std::destroy_at(&old_data[i]);  // for safe resources recycling
        }
        m_alloc.deallocate(old_data, old_capacity); 
    }

    size_t size() const noexcept {
        return m_size;
    }

    size_t capacity() const noexcept {
        return m_capacity;
    }

    bool empty() const noexcept {
        return m_size == 0;
    }

    // 当前系统支持的最大容量
    static constexpr size_t max_size() noexcept {
        return std::numeric_limits<size_t>::max() / sizeof(T);
    }

    T const& operator[](size_t i) const noexcept {
        return m_data[i];
    }

    T& operator[](size_t i) noexcept {
        return m_data[i];
    }

    T const& at(size_t i) const {
        if (i >= m_size) [[unlikely]] { throw std::out_of_range("Vector::at"); }
        return m_data[i];
    }

    T& at(size_t i) {
        if (i >= m_size) [[unlikely]] { throw std::out_of_range("Vector::at"); }
        return m_data[i];
    }    

    T const &front() const noexcept {
        return *m_data;
    }

    T& front() noexcept {
        return *m_data;
    }

    void push_back(T const& val) {
        if (m_size + 1 >= m_capacity) [[unlikely]] { reserve(m_capacity * 2); }
        std::construct_at(&m_data[m_size], val);
        m_size++;
    }

    void push_back(T&& val) {
        if (m_size + 1 >= m_capacity) [[unlikely]] { reserve(m_capacity * 2); }
        std::construct_at(&m_data[m_size], std::move(val));
        m_size++;
    }    

    // construct inplace
    template<class... Args>
    T& emplace_back(Args&&... args) {
        if (m_size + 1 >= m_capacity) [[unlikely]] { reserve(m_capacity * 2); }
    
        T *p = &m_data[m_size];
        std::construct_at(p, std::forward<Args>(args)...);
        m_size++;
    
        return *p;    
    }

    T *begin() noexcept {
        return m_data;
    }  

    T const *begin() const noexcept {
        return m_data;
    }

    T *end() noexcept {
        return m_data + m_size;
    }

    T const *end() const noexcept {
        return m_data + m_size;
    }

    std::reverse_iterator<T *> rbegin() noexcept {
        return std::make_reverse_iterator(m_data + m_size);
    }

    void pop_back() {
        m_size--;
        std::destroy_at(&m_data[m_size]);
    }

    T* erease(T const *it) noexcept(std::is_nothrow_move_assignable_v<T>) {
        size_t i = it - m_data;
        for (size_t j = i + 1; j < m_size; ++j) {
            m_data[j - 1] = std::move(m_data[j]);
        }
        m_size--;
        std::destroy_at(&m_data[m_size]);
        return const_cast<T *>(it);
    }

    T* erase(T const* first, T const* last) noexcept(std::is_nothrow_move_assignable_v<T>) {
        size_t diff = last - first;
        for (size_t j = last - m_data; j < m_size; ++j) {
            m_data[j - diff] = std::move(m_data[j]);
        }
        m_size -= diff;
        for (size_t i = m_size; i < m_size + diff; ++i) {
            std::destroy_at(&m_data[i]);
        }

        return const_cast<T *>(first);
    }

    void assign(size_t n, T const& val) {
        clear();
        reserve(n);
        m_size = n;

        for (size_t i = 0; i < n; ++i) {
            std::construct_at(&m_data[i], val);
        }
    }

    template<std::random_access_iterator InputIt>
    void assign(InputIt first, InputIt last) {
        clear();

        size_t n = last - first;
        reserve(n);
        m_size = n;

        for (size_t i = 0; i < n; ++i) {
            std::construct_at(&m_data[i], *first);
            ++first;
        }
    }

    void assign(std::initializer_list<T> ilist) {
        assign(ilist.begin(), ilist.end());
    }

    // emplace T element with args at it position.
    template<class ...Args>
    T* emplace(T const *it, Args&&... args) {
        size_t ipos = it - m_data;
        reserve(m_size + 1);

        // 从后向前逐个移动
        for (size_t i = m_size; i > ipos; --i) {
            std::construct_at(&m_data[i], std::move(m_data[i - 1]));
            std::destroy_at(&m_data[i - 1]);
        }

        m_size += 1;
        std::construct_at(&m_data[ipos], std::forward<Args>(args)...);
        return m_data + ipos;
    }

    bool operator==(Vector const& other) noexcept {
        return std::equal(begin(), end(), other.begin(), other.end());
    }

    // 输出三种比较结果
    auto operator<=>(Vector const& other) noexcept {
        return std::lexicographical_compare_three_way(begin(), end(), other.begin(), other.end());
    }
};