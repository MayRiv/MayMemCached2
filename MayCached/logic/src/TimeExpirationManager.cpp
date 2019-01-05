#include <TimeExpirationManager.hpp>
#include <thread>
#include <iostream>
#include <TimeExpirationCore.hpp>
namespace maycached {
namespace logic {
TimeExpirationManager::TimeExpirationManager(): m_IsRunning(false)
{

    m_TimeExpirationCore = std::make_unique<TimeExpirationCore>();
}

TimeExpirationManager::~TimeExpirationManager()
{
    if (m_IsRunning)
    {
        stopRepetitivelyRemovingExpired();
    }
}

bool TimeExpirationManager::addTimeMarker(const std::string &key, const std::chrono::time_point<std::chrono::system_clock> &t)
{
    return m_TimeExpirationCore->addTimeMarker(key, t);
}

bool TimeExpirationManager::removeTimeMarker(const std::string &key)
{
    return m_TimeExpirationCore->removeTimeMarker(key);
}

bool TimeExpirationManager::removeTimeMarkers(const std::chrono::time_point<std::chrono::system_clock> &t)
{
    return m_TimeExpirationCore->removeTimeMarkers(t);
}

bool TimeExpirationManager::setDeletionDelegate(std::function<bool (const std::string &)> f)
{
    m_TimeExpirationCore->setDeletionDelegate(f);
}

void TimeExpirationManager::startRepetitivelyRemoveExpired()
{
    m_IsRunning = true;
    m_Thread = std::thread(std::bind(&TimeExpirationManager::removeExpiredValuesRepetitively, this));
}

void TimeExpirationManager::stopRepetitivelyRemovingExpired()
{
    if (m_IsRunning)
    {
        {
            std::unique_lock<std::mutex> lock(m_StartStopMutex);
            m_IsRunning = false;
        }
        m_StartStopCondVar.notify_one();
        if (m_Thread.joinable())
        {
            m_Thread.join();
        }
        std::cout << "TImeExpirationManager has been stopped" << std::endl;
    }
    else {
        std::cout << "TimeExpirationManager is already stopped!" << std::endl;
    }
}

void TimeExpirationManager::removeExpiredValuesRepetitively()
{
    while(m_IsRunning)
    {
        std::cout << "Removing Expired Values" << std::endl;
        auto currentTime = std::chrono::system_clock::now();
        m_TimeExpirationCore->removeExpiredValues(currentTime);
        std::unique_lock<std::mutex> lock(m_StartStopMutex);
        if(m_IsRunning)
        {
            m_StartStopCondVar.wait_for(lock, std::chrono::minutes(1));
        }
    }
}

}
}
