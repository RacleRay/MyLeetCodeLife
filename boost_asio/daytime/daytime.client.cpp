/*************************************************************************
    > File Name: epcho.1.cpp
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time: 
 ************************************************************************/

#include <boost/asio/io_service.hpp>
#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main(int argc, char* argv[]) {
    try {
        if (argc != 2) {
            std::cerr << "Usage: client <host>" << std::endl;
            return 1;
        }

        // 和内核交互的窗口
        boost::asio::io_service io_service;

        // query可输入域名(/etc/hosts)或者地址，服务名(/etc/services)或者端口号
        // boost进行解析，但是DNS服务有可能会很耗时
        tcp::resolver resolver(io_service);
        tcp::resolver::query query(argv[1], "daytime");
        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

        // 创建socket
        tcp::socket socket(io_service);
        boost::asio::connect(socket, endpoint_iterator);

        for (;;) {
            boost::array<char, 128> buf;
            boost::system::error_code error; // boost error 设计更简洁一些

            // read_some, 不清楚会接收多大数据量。同步收
            size_t len = socket.read_some(boost::asio::buffer(buf), error);

            if (error == boost::asio::error::eof) {
                break;
            } else if (error) {
                throw boost::system::system_error(error);
            }

            std::cout.write(buf.data(), len);
        }
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
