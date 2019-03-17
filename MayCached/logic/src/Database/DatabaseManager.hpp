#ifndef DATABASE_MANAGER
#define DATABASE_MANAGER
#include "Database/IDatabaseManager.hpp"
#include <fstream>
namespace maycached {
namespace logic {
class Storage;
class ITimeExpirationManager;
class IDataMarshaller;
class DatabaseManager: public IStorageManager
{
public:
    DatabaseManager(std::unique_ptr<IDataMarshaller> dataMarshaller): m_DataMarshaller(std::move(dataMarshaller))
    {}

    std::fstream serializeToFile(const Storage&) const;
    std::unique_ptr<Storage> restoreFromFile(ITimeExpirationManager* timeManager)  const;
private:
    std::unique_ptr<IDataMarshaller> m_DataMarshaller;
};


} }
#endif //I_DATABASE_MARSHALLER
