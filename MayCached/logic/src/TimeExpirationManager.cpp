#include <TimeExpirationManager.hpp>
namespace maycached {
namespace logic {
TimeExpirationManager::TimeExpirationManager()
{
    m_Deleter = [&](const std::string&)->bool{
        return false;//empty
    };
}

bool TimeExpirationManager::addTimeMarker(const std::string &key, const std::chrono::time_point<std::chrono::system_clock> &t)
{

    std::unique_lock<std::shared_mutex> lock(m_EMMutex);
    m_ExpirationMarkers.insert({t,key});
    return true;
}

bool TimeExpirationManager::removeTimeMarker(const std::string &key)
{
    bool isDeleted{false};
    std::unique_lock<std::shared_mutex> lock(m_EMMutex);
    auto elementToDelete = m_ExpirationMarkers.end();
    for (auto it =  m_ExpirationMarkers.begin(); it != m_ExpirationMarkers.end(); it++)
    {
        if (key == it->second)
        {
            elementToDelete = it;
            break;
        }
    }
    if (elementToDelete != m_ExpirationMarkers.end())
    {
        m_ExpirationMarkers.erase(elementToDelete);
        isDeleted = true;
    }
    return isDeleted;
}

bool TimeExpirationManager::removeTimeMarkers(const std::chrono::time_point<std::chrono::system_clock> &t)
{
    std::unique_lock<std::shared_mutex> lock(m_EMMutex);
    m_ExpirationMarkers.erase(t);
    return true;
}

bool TimeExpirationManager::setDeletionDelegate(std::function<bool (const std::string &)> f)
{
    m_Deleter = f;
}


}
}
