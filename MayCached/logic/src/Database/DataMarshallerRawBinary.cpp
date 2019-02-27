
#include <optional>
#include <Database/DataMarshallerRawBinary.hpp>
#include <Data.hpp>
#include <cstdlib>
#include <memory>
#include <functional>
#include <cstring>
#include <chrono>
namespace maycached {
namespace logic {

IDataMarshaller::ManagedBuffer DataMarshallerRawBinary::serialize(const Data &data, uint64_t &totalSize) const
{
    const uint64_t keySize = data.key.size(); //problem with unicode
    const uint64_t valueSize = data.value.size();
    const bool shouldSaveTimestamp = data.willBeExpired.has_value();
    const std::chrono::system_clock::duration::rep timeTicks = shouldSaveTimestamp ? data.willBeExpired.value().time_since_epoch().count() : 0;
    totalSize = keySize + valueSize + sizeof(decltype (keySize)) + sizeof(decltype(valueSize)) //to encode length of strings
                    + sizeof(bool) //to encode whether we should save timestamp
                    + (shouldSaveTimestamp ? sizeof(timeTicks) : 0);

    IDataMarshaller::ManagedBuffer buffer(new char[totalSize]);

    auto bufferToWrite = buffer.get();
    bufferToWrite = saveField(bufferToWrite, keySize);
    bufferToWrite = saveString(bufferToWrite, data.key.c_str(), keySize);
    bufferToWrite = saveField(bufferToWrite, valueSize);
    bufferToWrite = saveString(bufferToWrite, data.value.c_str(), valueSize);
    bufferToWrite = saveField(bufferToWrite, shouldSaveTimestamp);
    if (shouldSaveTimestamp)
    {
        bufferToWrite = saveField(bufferToWrite, timeTicks);
    }
    return buffer;
}

Data DataMarshallerRawBinary::deserialize(const char* serializedData, uint64_t &size) const
{
    uint64_t keySize{0};
    uint64_t valueSize{0};
    std::string key;
    std::string value;
    bool shouldRestoreTimestamp{false};
    std::optional<std::chrono::time_point<std::chrono::system_clock>> expirationTime = std::nullopt;

    std::chrono::system_clock::duration::rep timeTicks{0};

    const char* bufferToRead = serializedData;
    bufferToRead = readField(bufferToRead, keySize);
    bufferToRead = readString(bufferToRead, key, keySize);
    bufferToRead = readField(bufferToRead, valueSize);
    bufferToRead = readString(bufferToRead,value, valueSize);
    bufferToRead = readField(bufferToRead, shouldRestoreTimestamp);
    if (shouldRestoreTimestamp)
    {
        bufferToRead = readField(bufferToRead, timeTicks);
        std::chrono::system_clock::duration duration(timeTicks);
        std::chrono::system_clock::time_point point(duration);
        expirationTime = std::make_optional(point);
    }

    Data result;
    result.key = key;
    result.value = value;
    result.willBeExpired =  expirationTime;

    size = bufferToRead - serializedData;

    return result;

}



}
}
