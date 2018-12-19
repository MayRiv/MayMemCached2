#ifndef TIMEEXPIRATIONCORE_HPP
#define TIMEEXPIRATIONCORE_HPP
#include <map>
#include <string>
#include <shared_mutex>
#include <functional>
namespace maycached {
namespace logic {


class TimeExpirationCore
{
public:
    TimeExpirationCore();
    bool addTimeMarker(const std::string& key,  const std::chrono::time_point<std::chrono::system_clock>& t);
    bool removeTimeMarkers(const std::chrono::time_point<std::chrono::system_clock> &t);
    bool removeTimeMarker(const std::string& key);
    bool setDeletionDelegate(std::function<bool(const std::string&)> f);
    void removeExpiredValues(const std::chrono::time_point<std::chrono::system_clock>);

private:
    std::function<bool (const std::string &)> m_Deleter;
    std::multimap<std::chrono::time_point<std::chrono::system_clock>, std::string> m_ExpirationMarkers;
    std::shared_mutex m_ExpirationMarkersMutex;
public:
    const decltype(m_ExpirationMarkers) getExpirationMarkers(){
        return m_ExpirationMarkers;
    }
};
}
}
#endif // TIMEEXPIRATIONCORE_HPP
