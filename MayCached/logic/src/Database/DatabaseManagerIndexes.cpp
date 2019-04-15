#include "Database/DatabaseManagerIndexes.hpp"
#include <storage.hpp>
#include <memory>
#include "Database/DataMarshallerFileHandler.hpp"
#include <iostream>
namespace maycached {
namespace logic {

bool DatabaseManagerIndexes::searchForValueAndExpiration(uint64_t offset, uint32_t fileId, std::string &value, std::optional<std::chrono::time_point<std::chrono::system_clock> > &willBeExpired) const
{
    std::fstream fs;
    fs.open("storage.b", std::fstream::binary | std::fstream::in | std::fstream::ate);
    std::cout << "test" << std::endl;
    std::filebuf* pbuf = fs.rdbuf();
    size_t size = pbuf->pubseekoff(0, fs.end);
    pbuf->pubseekpos(0);
    auto bufferPtr = std::unique_ptr<char[]>(new char[size]);
    auto buffer = bufferPtr.get();
    pbuf->sgetn(buffer, size);

    const char* shifted = buffer + offset;

    m_DataMarshaller->getValueAndTime(shifted, value, willBeExpired);

    return true;
}

std::fstream DatabaseManagerIndexes::serializeToFile(const Storage & storage) const
{
    std::fstream fs("storage.b", std::fstream::binary| std::fstream::out);

    return fs;
}

std::unique_ptr<Storage> DatabaseManagerIndexes::restoreFromFile(ITimeExpirationManager* timeManager) const
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

        auto&& indexes = m_DataMarshaller->deserialize(buffer, size, *this, 1);
        for (auto& index: indexes)
        {
            std::cout << "key " << index.key << " value " << index.getValue() << std::endl;
        }
    }

    return storage;

}

} }

