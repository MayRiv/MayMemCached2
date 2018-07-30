#ifndef SYSTEM_THREADPOOL
#define SYSTEM_THREADPOOL
#include <system/IThreadPool.hpp>
namespace maycached {
namespace system {
class ThreadPool: public IThreadPool {
public:
        void addTask();
};
} }
#endif


