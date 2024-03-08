#ifndef __ANY__H__
#define __ANY__H__

// A simple implementation of std::any

#include <memory>
#include <glog/logging.h>



class MyAny {
    struct BaseData {
        BaseData() = default;
        virtual ~BaseData() = default;

        virtual const std::type_info& getType() const = 0;
        virtual std::unique_ptr<BaseData> clone() const = 0;
    };

    template <typename T>
    struct Data: public BaseData {
        T m_data;

        Data(const T& data): m_data(data) {}
        Data(T&& data): m_data(std::move(data)) {}

        const std::type_info& getType() const override {
            return typeid(T);
        }

        std::unique_ptr<BaseData> clone() const override {
            return std::make_unique<Data<T>>(m_data);
        }
    };
    
    // pointer to the real data
    std::unique_ptr<BaseData> m_ptr;

public:
    MyAny() = default;
    ~MyAny() = default;

    MyAny(const MyAny& other) {
        if (other.m_ptr) {
            m_ptr = other.m_ptr->clone();
        }
    }

    MyAny &operator=(const MyAny& other) {
        // if (this != &other) {
        //     m_ptr = other.m_ptr->clone();
        // }
        m_ptr = std::move(MyAny(other).m_ptr);
        return *this;
    }

    MyAny(MyAny&& other) : m_ptr(std::move(other.m_ptr)) {}
    MyAny &operator=(MyAny&& other) {
        m_ptr = std::move(other.m_ptr);
        return *this;
    }

public:
    // Deal with : MyAny a = 1;
    template <typename T>
    using DecayType = typename std::decay<T>::type;

    // C++ 20
    template <typename T>
    requires (!std::is_same_v<std::decay_t<T>, MyAny>)
    MyAny(T&& data) {
        m_ptr = std::make_unique<Data<std::decay_t<T>>>(std::forward<T>(data));
    }

    template <
        typename T,
        typename std::enable_if<!std::is_same<DecayType<T>, MyAny>::value, bool>::type = true
    >
    MyAny& operator=(T&& data) {
        m_ptr = std::make_unique<Data<DecayType<T>>>(std::forward<T>(data));
        return *this;
    }

public:
    bool empty() const { return m_ptr == nullptr; }

    const std::type_info& getType() const {
        return (!empty()) ? m_ptr->getType() : typeid(void);
    }

    template<typename T>
    void checkType() const {
        if (getType().hash_code() != typeid(T).hash_code()) {
            LOG(FATAL) << "can not cast " << getType().name() << " to " << typeid(T).name();  
            // throw std::bad_cast();
        }
    }

    template <typename T>
    void checkBind() const {
        if (empty()) {
            LOG(FATAL) << "No data binuded to any";
            // throw std::bad_cast();
        }
        checkType<T>();
    }

    template <typename T>
    const T& cast() const {
        checkType<T>();
        checkBind<T>();
        return static_cast<const Data<T> *>(m_ptr.get())->m_data;
    }

    template <typename T>
    T &cast() {
        checkType<T>();
        checkBind<T>();
        return static_cast<Data<T> *>(m_ptr.get())->m_data;
    }
};


// helper function
template <typename T>
const T &any_cast(const MyAny &a) {
    return a.cast<T>();
}


template <typename T>
T &any_cast(MyAny &a) {
    return a.cast<T>();
}


#endif  //!__ANY__H__
