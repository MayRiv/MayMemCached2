#ifndef DATABASE_FILE_HANDLER_MARSHALLER
#define DATABASE_FILE_HANDLER_MARSHALLER
#include <optional>
#include <Database/IDataMarshaller.hpp>
#include <cstring>
#include <Data.hpp>
namespace maycached {
namespace logic {

class DataMarshallerFileHandler: public IDataMarshaller
{
    using ManagedBuffer = std::unique_ptr<char[]>;
public:
    std::vector<DbIndexData> deserialize(const char* buffer, uint64_t size, const IDatabaseManager& dbManager, uint32_t fileId);
    void getValueAndTime(const char *buffer, std::string &value, std::optional<std::chrono::time_point<std::chrono::system_clock> > &willBeExpired);
};


} }
#endif //DATABASE_FILE_HANDLER_MARSHALLER
