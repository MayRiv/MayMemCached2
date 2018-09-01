#ifndef STORAGE_HPP
#define STORAGE_HPP
#include <IStorage.hpp>
#include <Data.hpp>
#include <unordered_map>
#include <shared_mutex>
namespace maycached {
namespace logic {
class Storage: public IStorage
{
public:
    bool set(const std::string& key, const std::string& value, std::optional<uint32_t> expires) override;
    std::optional<std::string> get(const std::string& key) const override;
    bool sync(/*need to invent smth to decouple*/) const  override;
private:
    std::unordered_map<std::string, Data> m_Data;
    mutable std::shared_mutex m_SMutex;
};

} }
#endif
