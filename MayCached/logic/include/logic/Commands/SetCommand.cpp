#include <logic/Commands/SetCommand.hpp>
namespace maycached {
namespace logic {


const std::string& SetCommand::getKey() const
{
    return m_Key;
}

const std::string& SetCommand::getValue() const
{
    return m_Value;
}

std::optional<uint32_t> SetCommand::getExprires() const
{
    return m_Expires;
}

} }

