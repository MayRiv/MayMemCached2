#ifndef CLIENTSESSION_H
#define CLIENTSESSION_H
#include <boost/enable_shared_from_this.hpp>
#include <boost/core/noncopyable.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/socket_base.hpp>
#include <engine/IRequestController.hpp>
#include <gsl/pointers>
namespace maycached {
namespace connection {


class ClientSession: public boost::enable_shared_from_this<ClientSession>, boost::noncopyable
{
public:
    ClientSession(boost::asio::io_service& io_service, const gsl::not_null<engine::IRequestController*> controller);

    void start();
    void stop();

    bool isStarted() const { return m_Started;}

    boost::asio::ip::tcp::socket& getSocket() {
        return m_Socket;
    }
private:
    void doRead();
    void doWrite(const size_t size);
    void onWrite(const boost::system::error_code &err, size_t bytes);
    void onRead(const boost::system::error_code &err, size_t bytes);
    size_t isReadComplete(const boost::system::error_code &err, size_t bytes) const;

    static const size_t maxMessageSize = 1024;
    std::array<char, maxMessageSize> m_ReadBuffer{};
    std::array<char, maxMessageSize> m_WriteBuffer{};

    boost::asio::ip::tcp::socket               m_Socket;
    bool                                       m_Started;
    gsl::not_null<engine::IRequestController*> m_Engine;
};

} }
#endif // CLIENTSESSION_H
