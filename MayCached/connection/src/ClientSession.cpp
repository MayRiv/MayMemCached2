#include <ClientSession.hpp>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <engine/IResponse.hpp>
#include <iostream>

namespace maycached {
namespace connection {

ClientSession::ClientSession(boost::asio::io_service &io_service, const gsl::not_null<engine::IRequestController *> controller):m_Socket(io_service), m_Started(false), m_Engine(controller)
{
}

void ClientSession::start()
{
    m_Started = true;
    std::cout << "Started!" << std::endl;
    doRead();
}

void ClientSession::stop()
{
    if (m_Started)
    {
        m_Started = false;
    }
    m_Socket.close();
}
void ClientSession::doRead()
{
   boost::asio::async_read(m_Socket, boost::asio::buffer(m_ReadBuffer),
               std::bind(&ClientSession::isReadComplete, shared_from_this(), std::placeholders::_1, std::placeholders::_2),
               std::bind(&ClientSession::onRead, shared_from_this(), std::placeholders::_1, std::placeholders::_2));
}

void ClientSession::doWrite()
{

}

void ClientSession::onRead(const boost::system::error_code &err, size_t bytes)
{
    if (!err)
    {
        if (isStarted())
        {
            std::string unparsedCommand;
            std::copy_n(m_ReadBuffer.begin(), bytes, std::inserter(unparsedCommand,unparsedCommand.begin()));
            /*TODO: Blocker should be changed to async work*/
            auto response = m_Engine->handleRequest(unparsedCommand);
            std::cout <<  "We received an answer " << response << std::endl;
        } else
        {
            std::cout << "We have not started" << std::endl;
        }
    }
    else
    {
        std::cout <<  "Error while onRead, error message is " << err.message() << std::endl;
        stop();
    }
}

size_t ClientSession::isReadComplete(const boost::system::error_code &err, size_t bytes) const
{
    if (err)
        return 0;
    bool found = std::find(m_ReadBuffer.begin(), std::next(m_ReadBuffer.begin(), bytes), '\n') < std::next(m_ReadBuffer.begin(),bytes);
    return found ? 0 : 1;
}
void ClientSession::onWrite(const boost::system::error_code &err, size_t bytes)
{

}


} }
