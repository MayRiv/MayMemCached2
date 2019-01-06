#include <SUSDManager.hpp>
#include <iostream>
void maycached::mainapp::SUSDManager::launchMainApplicationShutdown()
{
    std::unique_lock<std::mutex> lock(m_StartStopMutex);
    m_StartStopCondVar.notify_one();
}

void maycached::mainapp::SUSDManager::suspendCurrentThreadUntilShutdown()
{
    std::unique_lock<std::mutex> lock(m_StartStopMutex);
    m_StartStopCondVar.wait(lock);
    std::cout << "Starting shutdown of mainapp." << std::endl;
}

void maycached::mainapp::SUSDManager::init(maycached::mainapp::SUSDManager::ComponentsCollection &&components)
{
    m_SusdableComponents = std::move(components);
}

void maycached::mainapp::SUSDManager::startApplication()
{
    for(auto it = m_SusdableComponents.rbegin(); it != m_SusdableComponents.rend(); it++)
    {
        (*it)->start();
    }
}

void maycached::mainapp::SUSDManager::stopApplication()
{
    for(auto it = m_SusdableComponents.begin(); it != m_SusdableComponents.end(); it++)
    {
        (*it)->stop();
    }
}
