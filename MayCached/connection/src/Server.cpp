#include <Server.hpp>
#include <ClientSession.hpp>

#include <boost/bind.hpp>
#include <boost/make_shared.hpp>
#include <iostream>
namespace maycached {
namespace connection {
Server::Server(const gsl::not_null<engine::IRequestController *> controller, unsigned short port):
    m_RequestController(controller),
    m_io_service(),
    m_acceptor(m_io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
{

}

Server::~Server()
{
    if (m_RunningThread.joinable())
    {
        m_RunningThread.join();
    }
}

void Server::run()
{
    auto session = boost::make_shared<ClientSession>(m_io_service, m_RequestController);
    m_acceptor.async_accept(session->getSocket(),boost::bind(&Server::handleAccept, this, session, _1));

    m_io_service.run();

}

void Server::start()
{
    if (!m_isRunning)
    {
        m_isRunning = true;
        m_RunningThread = std::thread(std::bind(&Server::run, this));
    }
}

void Server::stop()
{
    if (m_isRunning)
    {
        m_isRunning = false;
        m_io_service.stop();
        if (m_RunningThread.joinable())
        {
            m_RunningThread.join();
        }
        std::cout << " Server has been stopped" << std:: endl;
    }
}

void Server::handleAccept(boost::shared_ptr<ClientSession> session, const boost::system::error_code &err)
{
    if (m_isRunning)
    {
        std::cout << "new user!" << std::endl;
        session->start();

        auto newClient = boost::make_shared<ClientSession>(m_io_service, m_RequestController);
        m_acceptor.async_accept(newClient->getSocket(),boost::bind(&Server::handleAccept, this, newClient, _1));

    }
}

} }
