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
struct sync {};


template <typename T>
struct lazy {};


lazy<std::string> read_data() {
    Trace t;
    


}
