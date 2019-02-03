#ifndef IN_MEMORY_SERIALIZATION_STRATEGY_TEST
#define IN_MEMORY_SERIALIZATION_STRATEGY_TEST
#include "gtest/gtest.h"
#include <TimeExpirationManager.hpp>
#include <Storage.hpp>
#include <Database/InMemorySerializationStrategy.hpp>
#include <Database/DataMarshallerRawBinary.hpp>
#include <optional>
TEST(InMemorySerializationStrategyTest, serialize)
{
    auto timeExpirationManager = std::make_unique<maycached::logic::TimeExpirationManager>();
    auto storage = std::make_unique<maycached::logic::Storage>(timeExpirationManager.get());
    auto marshaller = std::make_unique<maycached::logic::DataMarshallerRawBinary>();
    auto serializaitonStrategy = std::make_unique<maycached::logic::InMemoryStrategy>(std::move(marshaller));

    storage->set("key", "value", 67);
    auto fs = serializaitonStrategy->serializeToFile(*storage.get());
    auto storage2 = serializaitonStrategy->restoreFromFile(std::move(fs), timeExpirationManager.get());
    EXPECT_EQ(storage->getData()["key"].value,storage->getData()["key"].value);

    EXPECT_EQ(storage->getData()["key"].willBeExpired,storage->getData()["key"].willBeExpired);
}

#endif
