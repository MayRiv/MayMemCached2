#ifndef TIMEEXPIRATIONMANAGER_HPP
#define TIMEEXPIRATIONMANAGER_HPP
#include <ITimeExpirationManager.hpp>
#include <map>
#include <string>
#include <shared_mutex>
namespace maycached {
namespace logic {


class TimeExpirationManager: public ITimeExpirationManager
{
public:
    TimeExpirationManager();
    bool addTimeMarker(const std::string& key,  const std::chrono::time_point<std::chrono::system_clock>& t) override;
    bool removeTimeMarkers(const std::chrono::time_point<std::chrono::system_clock> &t);
    bool removeTimeMarker(const std::string& key) override;
    bool setDeletionDelegate(std::function<bool(const std::string&)> f) override;
private:
    std::function<bool (const std::string &)> m_Deleter;
    std::multimap<std::chrono::time_point<std::chrono::system_clock>, std::string> m_ExpirationMarkers;
    std::shared_mutex m_EMMutex;
};
}
}
#endif // TIMEEXPIRATIONMANAGER_HPP
