#include <Storage.hpp>
#include <mutex>
#include <shared_mutex>
#include <Data.hpp>
#include <chrono>
#include <optional>
#include <unordered_map>
#include <ITimeExpirationManager.hpp>
namespace maycached {
namespace logic {

bool Storage::set(const std::string &key, const std::string &value, std::optional<uint32_t> expires)
{
    const auto now  = std::chrono::system_clock::now();
    const bool isExpired = expires.has_value();
    auto expirationTime = now;
    if (isExpired)
    {
        expirationTime = now + std::chrono::seconds(expires.value());
        m_TimeExpirationManager->addTimeMarker(key, expirationTime); //Remember that timeManager has inner lock, be careful for deadlocks
    }
    std::unique_lock<std::shared_mutex> lock(m_SMutex);


    m_HotInMemoryData[key] = Data{key, value, (isExpired
                   ? std::optional<decltype(now)>(expirationTime)
                   : std::nullopt)};

    return true;
}

std::optional<std::string> Storage::get(const std::string &key) const
{
    std::shared_lock<std::shared_mutex> lock(m_SMutex);
    auto it = m_HotInMemoryData.find(key);
    if (it != m_HotInMemoryData.end())
    {
        return std::optional<std::string>(it->second.value);
    }
    else
    {
        return std::nullopt;
    }
}

bool Storage::remove(const std::string &key)
{
    std::unique_lock<std::shared_mutex> lock(m_SMutex);
    bool isRemoved{false};
    auto it = m_HotInMemoryData.find(key);
    if (it != m_HotInMemoryData.end())
    {
        m_HotInMemoryData.erase(it);
        isRemoved = true;
    }

    return isRemoved;
}

bool Storage::del(const std::string &key)
{
    m_TimeExpirationManager->removeTimeMarker(key);
    return remove(key);
}

bool Storage::sync() const
{
    std::unique_lock<std::shared_mutex> lock(m_SMutex);
    return true;
}


} }

