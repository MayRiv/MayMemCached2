#ifndef EXPIRATION_CORE_TEST
#define EXPIRATION_CORE_TEST
#include "gtest/gtest.h"
#include <../src/TimeExpirationCore.hpp>

TEST(TimeExpirationCoreTest, addMarker)
{
    auto core  = std::make_unique<maycached::logic::TimeExpirationCore>();
    core->addTimeMarker("1", std::chrono::system_clock::now());

}

TEST(TimeExpirationCoreTest, removeExpired)
{
    auto core  = std::make_unique<maycached::logic::TimeExpirationCore>();
    auto now = std::chrono::system_clock::now();
    auto later = std::chrono::system_clock::now() + std::chrono::hours(10);
    core->addTimeMarker("1", now);
    core->addTimeMarker("2", later);
    EXPECT_EQ(core->getExpirationMarkers().size(), 2);

    core->removeExpiredValues(now + std::chrono::minutes(1));

    auto& result = core->getExpirationMarkers();
    EXPECT_EQ(result.size(), 1);
    if (result.size() > 0) //to not crash testset
    {
        auto savedValue = *core->getExpirationMarkers().begin();
        EXPECT_EQ(savedValue.second, "2");
    }
}

TEST(TimeExpirationCoreTest, removeExpiredMultipleValues)
{
    auto core  = std::make_unique<maycached::logic::TimeExpirationCore>();
    auto now = std::chrono::system_clock::now();
    auto later = std::chrono::system_clock::now() + std::chrono::hours(10);
    core->addTimeMarker("1", now);
    core->addTimeMarker("2", now + std::chrono::minutes(1));
    core->addTimeMarker("3", later);
    core->addTimeMarker("4", later + std::chrono::minutes(1));
    EXPECT_EQ(core->getExpirationMarkers().size(), 4);

    core->removeExpiredValues(now + std::chrono::minutes(3));

    auto& result = core->getExpirationMarkers();
    EXPECT_EQ(result.size(), 2);
    if (result.size() > 0) //to not crash testset
    {
        auto savedValue = *core->getExpirationMarkers().begin();
        EXPECT_EQ(savedValue.second, "3");
    }
}

TEST(TimeExpirationCoreTest, removeValueByKey)
{
    auto core  = std::make_unique<maycached::logic::TimeExpirationCore>();
    auto now = std::chrono::system_clock::now();
    core->addTimeMarker("1", now);

    EXPECT_EQ(core->getExpirationMarkers().size(), 1);

    core->removeTimeMarker("1");

    auto& result = core->getExpirationMarkers();
    EXPECT_EQ(result.size(), 0);
}
TEST(TimeExpirationCoreTest, removeExpiredMultipleValuesShuffled)
{
    auto core  = std::make_unique<maycached::logic::TimeExpirationCore>();
    auto now = std::chrono::system_clock::now();
    auto later = std::chrono::system_clock::now() + std::chrono::hours(10);
    core->addTimeMarker("8", later + std::chrono::minutes(5));
    core->addTimeMarker("1", now);
    core->addTimeMarker("2", now + std::chrono::minutes(1));
    core->addTimeMarker("3", later);
    core->addTimeMarker("4", later + std::chrono::minutes(1));
    core->addTimeMarker("5", now + std::chrono::minutes(4));
    core->addTimeMarker("6", now + std::chrono::minutes(2));
    core->addTimeMarker("7", later + std::chrono::minutes(15));

    EXPECT_EQ(core->getExpirationMarkers().size(), 8);

    core->removeExpiredValues(now + std::chrono::minutes(10));

    auto& result = core->getExpirationMarkers();
    EXPECT_EQ(result.size(), 4);
    if (result.size() > 0) //to not crash testset
    {
        auto savedValue = *core->getExpirationMarkers().begin();
        EXPECT_EQ(savedValue.second, "3");
    }
}
TEST(TimeExpirationCoreTest, addOneTimestamptValues)
{
    auto core  = std::make_unique<maycached::logic::TimeExpirationCore>();
    auto now = std::chrono::system_clock::now();

    core->addTimeMarker("1", now);
    core->addTimeMarker("2", now + std::chrono::minutes(10));
    core->addTimeMarker("3", now);

    EXPECT_EQ(core->getExpirationMarkers().size(), 3); //two values should be splashed

    core->removeExpiredValues(now + std::chrono::minutes(5));

    auto& result = core->getExpirationMarkers();
    EXPECT_EQ(result.size(), 1);
    if (result.size() > 0) //to not crash testset
    {
        auto savedValue = *core->getExpirationMarkers().begin();
        EXPECT_EQ(savedValue.second, "2");
    }
}
#endif
