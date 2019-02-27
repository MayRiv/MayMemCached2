/*#ifndef IN_MEMORY_STRATEGY
#define IN_MEMORY_STRATEGY
#include "Storages/StorageInMemory.hpp"
#include <fstream>
#include <Database/IDataMarshaller.hpp>
namespace maycached {
namespace logic {
class InMemoryStrategy: public IInMemorySerializationStrategy
{
public:
    InMemoryStrategy(StorageInMemory* storage, std::unique_ptr<IDataMarshaller> dataMarshaller): IInMemorySerializationStrategy(storage, std::move(dataMarshaller))
    {}
    std::fstream serializeToFile(const StorageInMemory&) const override;
    std::unique_ptr<StorageInMemory> restoreFromFile(std::fstream&& fs, ITimeExpirationManager *timeManager)  const override;
private:
};


} }
#endif //IN_MEMORY_STRATEGY
*/
