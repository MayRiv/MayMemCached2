#ifndef I_DATABASE_MANAGER
#define I_DATABASE_MANAGER
#include <memory>
class IStorage;
namespace maycached {
namespace logic {
class IStorageManager
{
public:
    /*virtual std::fstream serializeToFile(const IStorage&) const = 0;
    virtual std::unique_ptr<IStorage> restoreFromFile(std::fstream&& fs)  const = 0;*/
};


} }
#endif //I_DATABASE_MARSHALLER
