#include "Data.hpp"
#include "Database/IDatabaseManager.hpp"
#include <optional>
namespace maycached {
namespace logic {

std::string DbIndexData::getValue() const
{
    std::string value;
    std::optional<std::chrono::time_point<std::chrono::system_clock>> willBeExpired = std::nullopt;
    if (!m_DatabaseManager.searchForValueAndExpiration(m_Offset, m_FileId, value, willBeExpired))
    {
        value = "FAILED";
    }
    return value;

}

} }
