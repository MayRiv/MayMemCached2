
#include <optional>
#include <Database/DataMarshallerFileHandler.hpp>
#include <Data.hpp>
#include <cstdlib>
#include <memory>
#include <functional>
#include <cstring>
#include <chrono>
#include <iostream>
namespace maycached {
namespace logic {

std::vector<DbIndexData> DataMarshallerFileHandler::deserialize(const char *buffer, uint64_t size, const IDatabaseManager &dbManager, uint32_t fileId)
{
    std::cout << "Started!" <<  std::endl;
    decltype(size) curr = 0;
    std::vector<DbIndexData> result;
    while(curr != size)
    {
        std::string key;
        std::string value;
        bool shouldRestoreTimestamp{false};
        std::optional<std::chrono::time_point<std::chrono::system_clock>> expirationTime = std::nullopt;

        std::chrono::system_clock::duration::rep timeTicks{0};

        const char* bufferToRead = buffer;
        bufferToRead = parseKey(bufferToRead, key);
        bufferToRead = parseValueAndExpiration(bufferToRead, value, shouldRestoreTimestamp, timeTicks);
        if (shouldRestoreTimestamp)
        {
            std::chrono::system_clock::duration duration(timeTicks);
            std::chrono::system_clock::time_point point(duration);
            expirationTime = std::make_optional(point);
        }
        std::cout << "Trying to add value key - " << key << " curr " << curr << " fileId " << fileId << std::endl;
        result.emplace_back(key, dbManager, curr, fileId);
        result.back().getValue();
        auto shift = bufferToRead - buffer;

        buffer += shift;
        curr += shift;
    }
    return result;
}

void DataMarshallerFileHandler::getValueAndTime(const char* buffer, std::string &value, std::optional<std::chrono::time_point<std::chrono::system_clock> > &willBeExpired)
{
    std::string key;
    buffer = parseKey(buffer, key);

    std::chrono::system_clock::duration::rep ticks;
    bool shouldExpire = false;
    parseValueAndExpiration(buffer, value, shouldExpire, ticks);

    if (shouldExpire)
    {
        std::chrono::system_clock::duration duration(ticks);
        std::chrono::system_clock::time_point point(duration);
        willBeExpired = std::make_optional(point);
    }
    else {
        willBeExpired = std::nullopt;
    }
}


}
}
