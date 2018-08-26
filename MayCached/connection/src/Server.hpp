#ifndef CONNECTION_SERVER_HPP
#define CONNECTION_SERVER_HPP

#include <connection/IServer.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <engine/IRequestController.hpp>

namespace maycached {
namespace connection {

class ClientSession;

class Server: public IServer {
public:
    Server(std::weak_ptr<engine::IRequestController>, unsigned short port);
    void run() override;

private:
    void handleAccept(boost::shared_ptr<ClientSession> session, const boost::system::error_code & err);
    std::weak_ptr<engine::IRequestController> m_RequestController;

    boost::asio::io_service m_io_service;
    boost::asio::ip::tcp::acceptor m_acceptor;

};
} }
#endif
