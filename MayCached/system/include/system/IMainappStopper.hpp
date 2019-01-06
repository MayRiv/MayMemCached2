#ifndef STOPPER
#define STOPPER
namespace maycached {
namespace system {
class IMainappStopper
{
public:
    virtual void launchMainApplicationShutdown() = 0;
    virtual void suspendCurrentThreadUntilShutdown() = 0;
};


} }

#endif
