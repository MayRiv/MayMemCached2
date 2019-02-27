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
    ManagedBuffer serialize(const Data& data, uint64_t &totalSize) const override;
    Data deserialize(const char *serializedData, uint64_t& size) const override;
private:
    template<typename T>
    const char* readField(const char* buffer, T& target) const
    {
        target = *reinterpret_cast<const T*>(buffer);
        return buffer + sizeof(T);
    }

    const char* readString(const char* buffer, std::string& targetString, const size_t length) const
    {
        targetString = std::string{buffer, length};
        //std::memcpy(targetString, buffer, length);
        return buffer + length;
    }
    template<typename T>
    char* saveField(char* buffer, const T target ) const
    {
        std::memcpy(buffer, reinterpret_cast<const char*>(&target), sizeof(T));
        return buffer + sizeof(T);
    }
    char* saveString(char* buffer, const char* targetString, const size_t length) const
    {
        std::memcpy(buffer, targetString, length);
        return buffer + length;
    }
};


} }
#endif //DATABASE_MARSHALLER
