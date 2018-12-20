#include <logic/Commands/DeleteCommand.hpp>
namespace maycached {
namespace logic {

const std::string &DeleteCommand::getKey() const
{
    return m_Key;
}


} }
