#include <TimeExpirationCore.hpp>
#include <thread>
#include <iostream>
#include <experimental/map>
namespace maycached {
namespace logic {
TimeExpirationCore::TimeExpirationCore()
{
    m_Deleter = [&](const std::string&)->bool{
        return false;//empty
    };
}


bool TimeExpirationCore::addTimeMarker(const std::string &key, const std::chrono::time_point<std::chrono::system_clock> &t)
{

    std::unique_lock<std::shared_mutex> lock(m_ExpirationMarkersMutex);
    m_ExpirationMarkers.insert({t,key});
    return true;
}

bool TimeExpirationCore::removeTimeMarker(const std::string &key)
{
    bool isDeleted{false};
    std::unique_lock<std::shared_mutex> lock(m_ExpirationMarkersMutex);
    auto elementToDelete = m_ExpirationMarkers.end();
    for (auto it =  m_ExpirationMarkers.begin(); it != m_ExpirationMarkers.end(); it++) //TODO: should be refactored to find_if or even remove_if
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

bool TimeExpirationCore::removeTimeMarkers(const std::chrono::time_point<std::chrono::system_clock> &t)
{
    std::unique_lock<std::shared_mutex> lock(m_ExpirationMarkersMutex);
    m_ExpirationMarkers.erase(t);
    return true;
}

bool TimeExpirationCore::setDeletionDelegate(std::function<bool (const std::string &)> f)
{
    m_Deleter = f;
    return true;
}


void TimeExpirationCore::removeExpiredValues(const std::chrono::time_point<std::chrono::system_clock> time)
{
    auto expiredPredicate = [&time](const std::multimap<std::chrono::time_point<std::chrono::system_clock>, std::string>::value_type& v){
        return v.first < time;
    };
    std::unique_lock<std::shared_mutex> lock(m_ExpirationMarkersMutex);
    std::experimental::erase_if(m_ExpirationMarkers, expiredPredicate);
}


}
}
