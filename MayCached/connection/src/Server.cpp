#include <Server.hpp>
#include <ClientSession.hpp>

#include <boost/bind.hpp>
namespace maycached {
namespace connection {
Server::Server(std::weak_ptr<engine::IRequestController> controller, unsigned short port):m_RequestController(controller), m_io_service(),
                         m_acceptor(m_io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
{
}

void Server::run()
{
    auto session = std::make_shared<ClientSession>(m_io_service);
    m_acceptor.async_accept(session->getSocket(),boost::bind(&Server::handleAccept, this, session, _1));

    m_io_service.run();
}

void Server::handleAccept(std::shared_ptr<ClientSession> session, const boost::system::error_code &err)
{
    session->start();

    auto newClient = std::make_shared<ClientSession>(m_io_service);
    m_acceptor.async_accept(newClient->getSocket(),boost::bind(&Server::handleAccept, this, newClient, _1));
}

} }
