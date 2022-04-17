/*************************************************************************
    > File Name: echo.server.cpp
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time:
 ************************************************************************/

#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>


using boost::asio::ip::tcp;

std::string make_daytime_string() {
    using namespace std;  // For time_t, time and ctime;
    auto now = time(nullptr);
    return ctime(&now);  // const char*.  ctime 非线程安全
}

int main() {
    try {
        boost::asio::io_service io_service;

        // linux < 1024 的port 需要root权限
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 13));
        std::cout << "start service\n";

        // 同步接收和发送
        for (;;) {
            tcp::socket socket(io_service);
            acceptor.accept(socket);
            auto msg = make_daytime_string();
            boost::system::error_code ignored_error;
            boost::asio::write(socket, boost::asio::buffer(msg), ignored_error);
        }
        std::cout << "bye\n";
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
