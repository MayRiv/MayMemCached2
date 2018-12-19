#ifndef ITIMEEXPIRATIONMANAGER_HPP
#define ITIMEEXPIRATIONMANAGER_HPP
#include <string>
#include <functional>
#include <chrono>
namespace maycached {
namespace logic {
class ITimeExpirationManager
{
public:
    virtual bool addTimeMarker(const std::string& key,  const std::chrono::time_point<std::chrono::system_clock>& t) = 0;
    virtual bool removeTimeMarker(const std::string& key) = 0;
    virtual bool setDeletionDelegate(std::function<bool(const std::string&)> f) = 0;
    virtual ~ITimeExpirationManager() = default;
};
} }
#endif // ITIMEEXPIRATIONMANAGER_HPP
