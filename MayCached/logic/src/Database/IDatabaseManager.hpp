#ifndef I_DATABASE_MANAGER
#define I_DATABASE_MANAGER
#include <memory>
#include <string>
#include <chrono>
#include <optional>
class IData;
namespace maycached {
namespace logic {
class   IDatabaseManager
{
public:
    /*virtual std::fstream serializeToFile(const IStorage&) const = 0;
    virtual std::unique_ptr<IStorage> restoreFromFile(std::fstream&& fs)  const = 0;*/
    virtual bool searchForValueAndExpiration(uint64_t offset, uint32_t fileId, std::string& value, std::optional<std::chrono::time_point<std::chrono::system_clock>>& willBeExpired) const = 0;
};


} }
#endif //I_DATABASE_MARSHALLER
