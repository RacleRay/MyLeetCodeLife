/*************************************************************************
    > File Name: asio.2.cpp
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time:
 ************************************************************************/

#include <boost/asio.hpp>
#include <boost/asio/steady_timer.hpp>  // 新的timer
#include <iostream>
//#include <boost/date_time/posix_time/posix_time.hpp>  // 老的timer

void callback(const boost::system::error_code&) {
    std::cout << "Hello, world!" << std::endl;
}

void callback2(const boost::system::error_code&) {
    std::cout << "second call but first run" << std::endl;
}

int main() {
    boost::asio::io_service   io;
    boost::asio::steady_timer st(io);
    st.expires_from_now(std::chrono::seconds(5));
    st.wait();
    std::cout << "hello world\n";
    return 0;
}
