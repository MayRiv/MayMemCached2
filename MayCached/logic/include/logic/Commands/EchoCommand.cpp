#include <logic/Commands/EchoCommand.hpp>
namespace maycached {
namespace logic {

const std::string &EchoCommand::getMessage() const
{
    return m_Message;
}

} }

