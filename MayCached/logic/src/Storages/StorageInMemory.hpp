#ifndef STORAGE_HPP
#define STORAGE_HPP
#include <Storages/IStorage.hpp>
#include <Data.hpp>
#include <unordered_map>
#include <shared_mutex>
#include <ITimeExpirationManager.hpp>
#include "Database/IDataMarshaller.hpp"
#include "ITimeExpirationManager.hpp"
#include <fstream>
namespace maycached {
namespace logic {
class IInMemorySerializationStrategy;

class StorageInMemory: public IStorage
{
public:

    StorageInMemory(ITimeExpirationManager* timeExpirationManager): m_TimeExpirationManager(timeExpirationManager)
    {
        m_TimeExpirationManager->setDeletionDelegate(std::bind(&StorageInMemory::removeExpired, this, std::placeholders::_1));
    }
    bool set(const std::string& key, const std::string& value, std::optional<uint32_t> expires) override;
    bool set(const Data& data){
        std::unique_lock<std::shared_mutex> lock(m_SMutex);
        m_Data[data.key] = data;
    }
    std::optional<std::string> get(const std::string& key) const override;
    bool removeExpired(const std::string& key) override;
    bool del(const std::string& key) override;
    bool sync(/*need to invent smth to decouple*/) const  override;
    const std::unordered_map<std::string, Data> getData() {
        std::unique_lock<std::shared_mutex> lock(m_SMutex); //should check whether this is enough
        return m_Data;
    }
private:

    std::unordered_map<std::string, Data> m_Data;
    mutable std::shared_mutex m_SMutex;
    ITimeExpirationManager* m_TimeExpirationManager;
};


/*
class IInMemorySerializationStrategy
{
public:
    IInMemorySerializationStrategy(StorageInMemory* Storage, std::unique_ptr<IDataMarshaller> dataMarshaller):m_DataMarshaller(std::move(dataMarshaller)), m_Storage(Storage)
    {}
    virtual std::fstream serializeToFile(const StorageInMemory&) const = 0;
    virtual std::unique_ptr<StorageInMemory> restoreFromFile(std::fstream&& fs, ITimeExpirationManager*)  const = 0;
protected:
    std::unordered_map<std::string, Data> getCollection() const
    {
        return  m_Storage->getData(); //check this stuff, this looks odd, but right now is 2 AM, I can miss stuff.
    }
    void addData(const Data& data) const{
        m_Storage->set(data);
    }
    std::unique_ptr<IDataMarshaller> m_DataMarshaller;
private:
    StorageInMemory* m_Storage;
};

class InMemoryStrategy: public IInMemorySerializationStrategy
{
public:
    InMemoryStrategy(StorageInMemory* storage, std::unique_ptr<IDataMarshaller> dataMarshaller): IInMemorySerializationStrategy(storage, std::move(dataMarshaller))
    {}
    std::fstream serializeToFile(const StorageInMemory&) const override
    {
        std::fstream fs("storage.b", std::fstream::binary);
        auto data = getCollection();
        for (auto val: data)
        {
            uint64_t size;
            auto buffer = m_DataMarshaller->serialize(val.second, size);
            fs.write(buffer.get(), size);
        }
        fs.close();
        return fs;
    }
    std::unique_ptr<StorageInMemory> restoreFromFile(std::fstream&& fs, ITimeExpirationManager *timeManager)  const override
    {
        fs.open("storage.b", std::fstream::binary | std::fstream::ate);

        auto storage = std::make_unique<StorageInMemory>(std::move(timeManager));
        std::filebuf* pbuf = fs.rdbuf();
        size_t size = pbuf->pubseekoff(0, fs.end);
        pbuf->pubseekpos(0);
        auto bufferPtr = std::unique_ptr<char[]>(new char[size]);
        auto buffer = bufferPtr.get();
        pbuf->sgetn(buffer, size);
        size_t curr = 0;
        while(curr != size)
        {
            uint64_t size{0};
            auto data = m_DataMarshaller->deserialize(buffer, size);
            addData(data);
            buffer += size;
            curr += size;
        }
        return storage;
    }
private:
};




*/
} }
#endif
