#ifndef SUSDMANAGER
#define SUSDMANAGER
#include <system/IComponent.hpp>
#include <system/IMainappStopper.hpp>
#include <array>
#include <memory>
#include <shared_mutex>
//#include <atomic>
#include <condition_variable>
#include <thread>
#include <gsl/pointers>
namespace maycached {
namespace mainapp {
enum class InitPriority :uint8_t
{
    E_CONNECTION = 0,
    E_ENGINE,
    E_LOGIC,
    E_MAX
};
constexpr uint8_t COMPONENTS_SIZE = static_cast<uint8_t>(InitPriority::E_MAX);
class SUSDManager: public system::IMainappStopper
{
public:
    using ComponentsCollection = std::array<system::IComponent*, COMPONENTS_SIZE>;
    SUSDManager() = default;
    void launchMainApplicationShutdown() override;
    void suspendCurrentThreadUntilShutdown() override;
    void init(ComponentsCollection&& components);
    void startApplication();
    void stopApplication();

    virtual ~SUSDManager() = default;
private:
    ComponentsCollection m_SusdableComponents;

    //std::atomic<bool> m_IsRunning;
    std::condition_variable m_StartStopCondVar;
    std::mutex m_StartStopMutex;


};

} }

#endif
