#include <TimeExpirationCore.hpp>
#include <thread>
#include <iostream>
#include <experimental/map>
#include <set>
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
    bool isDeleted{true};
    std::unique_lock<std::shared_mutex> lock(m_ExpirationMarkersMutex);

    std::cout << "Removing time marker for " << key << std::endl;
    std::experimental::erase_if(m_ExpirationMarkers, [&key](const auto& marker){
                                    return marker.second == key;
                                });
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
    std::set<std::string> toBeDeleted{};
    {
        std::unique_lock<std::shared_mutex> lock(m_ExpirationMarkersMutex);
        auto endOfExpired = m_ExpirationMarkers.begin();
        while(endOfExpired != m_ExpirationMarkers.end())
        {
            if (expiredPredicate(*endOfExpired))
            {
                toBeDeleted.emplace(endOfExpired->second);
                endOfExpired++;
            }
            else
            {
               break;
            }
        }
        std::cout << "We are about to remove " << std::distance(m_ExpirationMarkers.begin(), endOfExpired) << " markers" << std::endl;
        m_ExpirationMarkers.erase(m_ExpirationMarkers.begin(), endOfExpired);
    }
    for(auto it: toBeDeleted) //to be sure that we 100% will not have a deadlock, we should call callback not under the lock
    {
        m_Deleter(it);
    }
}


}
}
