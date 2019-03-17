#ifndef DATA_HPP
#define DATA_HPP
#include <chrono>
#include <optional>
#include <string>
namespace maycached {
namespace logic {
class IData
{
public:
    IData() = default;
    IData(std::string inKey): key(std::move(inKey))
    {}
    std::string key;
    virtual const std::string& getValue() const = 0;
    virtual std::optional<std::chrono::time_point<std::chrono::system_clock>> getExpirationTime() const = 0;
};

class Data : public IData
{
public:
    Data() = default;
    Data(std::string key, std::string inValue,  std::optional<std::chrono::time_point<std::chrono::system_clock>> expiration):
        IData(std::move(key)),
        value(std::move(inValue)),
        willBeExpired(expiration)
    {}
    const std::string& getValue() const override {
        return value;
    }
    std::optional<std::chrono::time_point<std::chrono::system_clock>> getExpirationTime() const override{
        return willBeExpired;
    }
    std::string value;
    std::optional<std::chrono::time_point<std::chrono::system_clock>> willBeExpired = std::nullopt;
};

} }
#endif
