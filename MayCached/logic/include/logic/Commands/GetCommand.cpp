#include <logic/Commands/GetCommand.hpp>
namespace maycached {
namespace logic {

const std::string &GetCommand::getKey() const
{
    return m_Key;
}

} }

