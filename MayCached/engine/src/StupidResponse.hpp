#ifndef STUPID_RESPONSE_HPP
#define STUPID_RESPONSE_HPP
#include <string>
#include <engine/IResponse.hpp>
namespace maycached {
namespace engine {
class StupidResponse: public IResponse
{
public:
    StupidResponse(const std::string& message): m_Message(message){}
    std::string toString() const override;

private:
    std::string m_Message;
};

} }
#endif // STUPID_RESPONSE_HPP
