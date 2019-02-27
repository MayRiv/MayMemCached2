#ifndef IN_MEMORY_STRATEGY
#define IN_MEMORY_STRATEGY
#include "Storage.hpp"
#include <fstream>
#include <Database/IDataMarshaller.hpp>
namespace maycached {
namespace logic {
class InMemoryStrategy
{
public:
    InMemoryStrategy(std::unique_ptr<IDataMarshaller> dataMarshaller): m_DataMarshaller(std::move(dataMarshaller))
    {}
    std::fstream serializeToFile(const Storage&) const ;
    std::unique_ptr<Storage> restoreFromFile(std::fstream&& fs, ITimeExpirationManager *timeManager)  const;
private:
    std::unique_ptr<IDataMarshaller> m_DataMarshaller;
};


} }
#endif //IN_MEMORY_STRATEGY
