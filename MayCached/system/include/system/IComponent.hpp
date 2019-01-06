#ifndef ICOMPONENT
#define ICOMPONENT
#include <atomic>
namespace maycached {
namespace system {
class IComponent
{
public:
    IComponent():m_isRunning(false){}
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual ~IComponent() = default;
protected:
    std::atomic<bool> m_isRunning;
};

} }
#endif
