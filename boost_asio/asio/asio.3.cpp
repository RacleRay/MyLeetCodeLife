/*************************************************************************
    > File Name: asio.3.cpp
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time:
 ************************************************************************/


#include <boost/asio.hpp>
#include <boost/bind/bind.hpp> 
#include <boost/date_time/posix_time/posix_time.hpp>
#include <iostream>
#include <memory>
#include <vector>

// boost::function<>
// std::function<>


/* ============================================================================ */
void print2(const boost::system::error_code& e,
           boost::asio::deadline_timer* t, int* count) {
    if (*count < 5) {
        std::cout << *count << std::endl;
        ++(*count);

        t->expires_at(t->expires_at() + boost::posix_time::seconds(1));
        t->async_wait([t, count](const auto& error) { print2(error, t, count); });
    }
}
/*
 * 以下函数 shared_ptr 没有增加counting值，退出函数 t 应该被销毁，所以会出错
 * 但是有时又能正常运行，这显示是不合理的。错误的写法。
 * */
std::shared_ptr<boost::asio::deadline_timer>
registerPrint2(boost::asio::io_service& io, int* count) {
    auto t = std::make_shared<boost::asio::deadline_timer>(io, boost::posix_time::seconds(1));
    // shared_ptr without counting increse.
    auto pt = t.get();
    t->async_wait([pt, count](const auto& error) { print2(error, pt, count); });
    return t;
}

/* ============================================================================ */
// 以下方式，改变参数类型为 shared_ptr，增加引用计数，防止出现野指针，
// 代价是可能很多地方参数类型都要改
void print3(const boost::system::error_code& e,
           std::shared_ptr<boost::asio::deadline_timer> t, int* count) {
    if (*count < 5) {
        std::cout << *count << std::endl;
        ++(*count);

        t->expires_at(t->expires_at() + boost::posix_time::seconds(1));
        // std::bind 返回的是 function 对象，无法inline，且类占用空间更大
        // lambda 比function的方式更高效一些，空间开销一些，默认inline; 
        t->async_wait([t, count](const auto& error) { print3(error, t, count); });
        // 和以下写法意思一致
        // t->async_wait(boost::bind(print, boost::asio::placeholders::error, t, count));
    }
}

std::shared_ptr<boost::asio::deadline_timer>
registerPrint3(boost::asio::io_service& io, int* count) {
    auto t = std::make_shared<boost::asio::deadline_timer>(io, boost::posix_time::seconds(1));
    t->async_wait([t, count](const auto& error) { print3(error, t, count); });
    return t;
}

int main() {
    boost::asio::io_service io;

    std::vector<int> v;

    for (int i = 0; i < 5; ++i)
        v.push_back(i);

    // registerPrint2 中的 t，出了这个for loop，就会被析构，而可能导致异步的任务中 t 成了野指针
    for (int i = 0; i < 5; ++i) {
        //auto t = registerPrint3(io, &v[i]);
        auto t = registerPrint2(io, &v[i]);
        std::cout << "pointer address is: " << t.get() << std::endl;
    }
    
    io.run();
    for (int i = 0; i < 5; ++i)
        std::cout << "Final count is " << v[i] << std::endl;

    return 0;
}
