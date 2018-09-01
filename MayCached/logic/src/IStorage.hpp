#ifndef I_STORAGE_HPP
#define I_STORAGE_HPP
#include <optional>
namespace maycached {
namespace logic {
class IStorage
{
public:
    virtual bool set(const std::string& key, const std::string& value, std::optional<uint32_t> expires) = 0;
    virtual std::optional<std::string> get(const std::string& key) const = 0;
    virtual bool sync(/*need to invent smth to decouple*/) const = 0;
    /*virtual bool updateExpired() = 0;*/
};

} }
#endif