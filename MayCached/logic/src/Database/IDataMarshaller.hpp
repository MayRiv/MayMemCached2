#ifndef I_DATABASE_MARSHALLER
#define I_DATABASE_MARSHALLER
#include <optional>
#include <functional>
#include <memory>
#include <Data.hpp>
namespace maycached {
namespace logic {
class IDataMarshaller
{
public:
    using ManagedBuffer = std::unique_ptr<char[]>;
    virtual ManagedBuffer serialize(const Data& data, uint64_t &size) const = 0;
    virtual Data deserialize(const char* serializedData, uint64_t& size)  const = 0;
};


} }
#endif //I_DATABASE_MARSHALLER
