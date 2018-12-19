#ifndef TIMEEXPIRATIONMANAGER_HPP
#define TIMEEXPIRATIONMANAGER_HPP
#include <ITimeExpirationManager.hpp>
#include <map>
#include <string>
#include <shared_mutex>
#include <atomic>
#include <condition_variable>
#include <thread>

namespace maycached {
namespace logic {

class TimeExpirationCore;

class TimeExpirationManager: public ITimeExpirationManager
{
public:
    TimeExpirationManager();
    ~TimeExpirationManager() override;
    bool addTimeMarker(const std::string& key,  const std::chrono::time_point<std::chrono::system_clock>& t) override;
    bool removeTimeMarkers(const std::chrono::time_point<std::chrono::system_clock> &t);
    bool removeTimeMarker(const std::string& key) override;
    bool setDeletionDelegate(std::function<bool(const std::string&)> f) override;
    void startRepetitivelyRemoveExpired() override;
    void stopRepetitivelyRemovingExpired() override;
private:
    void removeExpiredValuesRepetitively();
    //void removeExpiredValues(const std::chrono::time_point<std::chrono::system_clock>);


    std::atomic<bool> m_IsRunning;
    std::condition_variable m_StartStopCondVar;
    std::mutex m_StartStopMutex;
    std::thread m_Thread;
    /*std::function<bool (const std::string &)> m_Deleter;
    std::multimap<std::chrono::time_point<std::chrono::system_clock>, std::string> m_ExpirationMarkers;*/

    std::unique_ptr<class TimeExpirationCore> m_TimeExpirationCore;
};
}
}
#endif // TIMEEXPIRATIONMANAGER_HPP
