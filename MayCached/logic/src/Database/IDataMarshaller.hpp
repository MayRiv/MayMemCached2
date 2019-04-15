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
    /*virtual ManagedBuffer serialize(const Data& data, uint64_t &size) const = 0;
    virtual Data deserializeWholeDataItem(const char* serializedData, uint64_t& size)  const = 0;*/


    //TODO: Move implementation here
    /*virtual const char* parseValueAndExpiration(const char* serializedData, std::string& value, bool& shouldExpire, std::chrono::system_clock::duration::rep& ticks) const = 0;
    virtual const char* parseKey(const char* serializedData, std::string& key) const = 0;*/

    const char* parseKey(const char* serializedData, std::string& key) const
    {
        uint64_t keySize{0};
        serializedData = readField(serializedData, keySize);
        serializedData = readString(serializedData, key, keySize);
        return serializedData;
    }
    const char* parseValueAndExpiration(const char* serializedData, std::string& value,
                                        bool& shouldExpire, std::chrono::system_clock::duration::rep& ticks) const
    {
        uint64_t valueSize{0};
        const char * bufferToRead = readField(serializedData, valueSize);
        bufferToRead = readString(bufferToRead,value, valueSize);
        bufferToRead = readField(bufferToRead, shouldExpire);
        if (shouldExpire)
        {
            bufferToRead = readField(bufferToRead, ticks);
            std::chrono::system_clock::duration duration(ticks);
            //std::chrono::system_clock::time_point point(duration);
            //expirationTime = std::make_optional(point);
        }
        return bufferToRead;
    }

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
#endif //I_DATABASE_MARSHALLER
