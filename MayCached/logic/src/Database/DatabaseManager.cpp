#include "Database/DatabaseManager.hpp"
#include <storage.hpp>
#include <memory>
#include "Database/DataMarshallerRawBinary.hpp"
#include <iostream>
namespace maycached {
namespace logic {

bool DatabaseManager::searchForValueAndExpiration(uint64_t offset, uint32_t fileId, std::string &value, std::optional<std::chrono::time_point<std::chrono::system_clock> > &willBeExpired) const
{
    return false;
}

std::fstream DatabaseManager::serializeToFile(const Storage & storage) const
{
    std::fstream fs("storage.b", std::fstream::binary| std::fstream::out);
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

std::unique_ptr<Storage> DatabaseManager::restoreFromFile(ITimeExpirationManager* timeManager) const
{
    std::fstream fs;
    fs.open("storage.b", std::fstream::binary | std::fstream::in | std::fstream::ate);
    auto storage = std::make_unique<Storage>(timeManager);

    if (!fs.fail())
    {
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
            auto data = m_DataMarshaller->deserializeWholeDataItem(buffer, size);
            storage->set(data);
            buffer += size;
            curr += size;
        }
    }

    return storage;

}

} }

