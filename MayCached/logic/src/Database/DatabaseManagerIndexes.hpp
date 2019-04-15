#ifndef DATABASE_INDEXES_MANAGER
#define DATABASE_INDEXES_MANAGER
#include "Database/IDatabaseManager.hpp"

#include <fstream>
namespace maycached {
namespace logic {
class Storage;
class ITimeExpirationManager;
class DataMarshallerFileHandler;
class DatabaseManagerIndexes: public IDatabaseManager
{
public:
    DatabaseManagerIndexes(std::unique_ptr<DataMarshallerFileHandler> dataMarshaller): m_DataMarshaller(std::move(dataMarshaller))
    {}

    virtual bool searchForValueAndExpiration(uint64_t offset, uint32_t fileId, std::string& value, std::optional<std::chrono::time_point<std::chrono::system_clock>>& willBeExpired) const override;
    std::fstream serializeToFile(const Storage&) const;
    std::unique_ptr<Storage> restoreFromFile(ITimeExpirationManager* timeManager)  const;
private:
    std::unique_ptr<DataMarshallerFileHandler> m_DataMarshaller;
    uint32_t fileId = 0;
};


} }
#endif //DATABASE_INDEXES_MANAGER
