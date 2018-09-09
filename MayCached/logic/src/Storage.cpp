#include <Storage.hpp>
#include <mutex>
#include <shared_mutex>
#include <Data.hpp>
#include <chrono>
#include <optional>
namespace maycached {
namespace logic {

bool Storage::set(const std::string &key, const std::string &value, std::optional<uint32_t> expires)
{
    auto now  = std::chrono::system_clock::now();
    std::unique_lock<std::shared_mutex> lock(m_SMutex);

    m_Data[key] = {key, value, (expires.has_value()
                   ? std::optional<decltype(now)>(now + std::chrono::seconds(expires.value()))
                   : std::nullopt)};

    return true;
}

std::optional<std::string> Storage::get(const std::string &key) const
{
    std::shared_lock<std::shared_mutex> lock(m_SMutex);
    auto it = m_Data.find(key);
    if (it != m_Data.end())
    {
        return std::optional<std::string>(it->second.value);
    }
    else
    {
        return std::nullopt;
    }
}

bool Storage::sync() const
{
    std::unique_lock<std::shared_mutex> lock(m_SMutex);
}


} }

