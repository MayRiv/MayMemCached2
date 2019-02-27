#include "Database/InMemorySerializationStrategy.hpp"
#include <fstream>
#include <memory>
#include "Storages/StorageInMemory.hpp"
namespace maycached {
namespace logic {

std::fstream InMemoryStrategy::serializeToFile(const Storage & storage) const
{
    std::fstream fs("/home/may/storage.b", std::fstream::binary| std::fstream::out);
    auto data = storage.getData();
    for (auto val: data)
    {
        uint64_t size;
        auto buffer = m_DataMarshaller->serialize(val.second, size);
        fs.write(buffer.get(), size);
    }
    fs.close();
    return fs;
}

std::unique_ptr<Storage> InMemoryStrategy::restoreFromFile(std::fstream &&fs, ITimeExpirationManager *timeManager) const
{
    fs.open("/home/may/storage.b", std::fstream::binary | std::fstream::in | std::fstream::ate);

    auto storage = std::make_unique<Storage>(std::move(timeManager));
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
        storage->set(data);
        buffer += size;
        curr += size;
    }
    return storage;

}



} }

