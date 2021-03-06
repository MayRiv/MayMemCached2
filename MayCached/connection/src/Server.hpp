#ifndef CONNECTION_SERVER_HPP
#define CONNECTION_SERVER_HPP

#include <connection/IServer.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <engine/IRequestController.hpp>
#include <gsl/pointers>
#include <thread>
#include <atomic>

namespace maycached {
namespace connection {

class ClientSession;

class Server: public IServer
{
public:
    Server(const gsl::not_null<engine::IRequestController*>, unsigned short port);
    ~Server();

    void start() override;
    void stop() override;
private:
    void run() override;
    void handleAccept(boost::shared_ptr<ClientSession> session, const boost::system::error_code & err);
    gsl::not_null<engine::IRequestController*> m_RequestController;

    boost::asio::io_service m_io_service;
    boost::asio::ip::tcp::acceptor m_acceptor;
    std::thread m_RunningThread;

};
} }
#endif
