#ifndef STORAGE_HPP
#define STORAGE_HPP
#include <IStorage.hpp>
#include <Data.hpp>
#include <unordered_map>
#include <shared_mutex>
#include <ITimeExpirationManager.hpp>
namespace maycached {
namespace logic {
class IInMemorySerializationStrategy;
class Storage: public IStorage
{
public:
    Storage(ITimeExpirationManager* timeExpirationManager):
        m_TimeExpirationManager(timeExpirationManager)
    {
        m_TimeExpirationManager->setDeletionDelegate(std::bind(&Storage::remove, this, std::placeholders::_1));
    }
    bool set(const std::string& key, const std::string& value, std::optional<uint32_t> expires) override;
    bool set(const Data& data){
        std::unique_lock<std::shared_mutex> lock(m_SMutex);
        m_Data[data.key] = data;
		return true;
    }
    std::optional<std::string> get(const std::string& key) const override;
    bool remove(const std::string& key) override;
    bool del(const std::string& key) override;
    bool sync(/*need to invent smth to decouple*/) const  override;
    std::unordered_map<std::string, Data> getData() const {
        std::shared_lock<std::shared_mutex> lock(m_SMutex); //not sure that this will be enough
        return m_Data;
    }
private:
    std::unordered_map<std::string, Data> m_Data;
    mutable std::shared_mutex m_SMutex;
    ITimeExpirationManager* m_TimeExpirationManager;
};

} }
#endif
