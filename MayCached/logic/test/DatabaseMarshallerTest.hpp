#ifndef DATABASE_MARSHALLER_TEST
#define DATABASE_MARSHALLER_TEST
#include "gtest/gtest.h"
#include <../src/Database/DataMarshallerRawBinary.hpp>
#include <../src/Data.hpp>
#include <memory>
#include <iostream>
#include <memory>
#include <cstring>
TEST(DatabaseMarshallerTest, checkDeserializeSerializedNoTime)
{
    maycached::logic::DataMarshallerRawBinary marshaller;
    maycached::logic::Data data;
    data.key = "bra";
    data.value = "foo0";
    data.willBeExpired = std::nullopt;
    uint64_t size;
    uint64_t size2;
    auto buffer = marshaller.serialize(data, size);
    auto data2 = marshaller.deserialize(buffer.get(), size2);
    EXPECT_EQ(data.key,data2.key);

    EXPECT_EQ(data.value,data2.value);
    EXPECT_EQ(size,size2);
}

TEST(DatabaseMarshallerTest, checkDeserializeSerializedWithTime)
{
    maycached::logic::DataMarshallerRawBinary marshaller;
    maycached::logic::Data data;
    data.key = "braadf";
    data.value = "foo0adf";
    data.willBeExpired = std::make_optional(std::chrono::system_clock::now());
    uint64_t size, size2;

    auto buffer = marshaller.serialize(data, size);
    auto data2 = marshaller.deserialize(buffer.get(), size2);
    EXPECT_EQ(data.key,data2.key);

    EXPECT_EQ(data.value,data2.value);
    EXPECT_EQ(size,size2);

    EXPECT_EQ(data.willBeExpired, data2.willBeExpired);
}

#endif
