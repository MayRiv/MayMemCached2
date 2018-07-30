#include <iostream>
#include <boost/asio/io_service.hpp>
#include <boost/atomic.hpp>
#include <connection/IServer.hpp>
int main()
{
    boost::asio::io_service service;
    boost::atomic<int> a;

    std::cout << "Hello World!" << std::endl;
    return 0;
}
