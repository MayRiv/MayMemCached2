#ifndef DATABASE_MARSHALLER
#define DATABASE_MARSHALLER
#include <optional>
#include <Database/IDataMarshaller.hpp>
#include <cstring>
namespace maycached {
namespace logic {

class DataMarshallerRawBinary: public IDataMarshaller
{
public:
    ManagedBuffer serialize(const Data& data, uint64_t &totalSize) const;
    Data deserializeWholeDataItem(const char *serializedData, uint64_t& size) const;


};


} }
#endif //DATABASE_MARSHALLER
