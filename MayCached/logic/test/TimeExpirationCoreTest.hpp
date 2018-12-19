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
        /*auto savedValue = *core->getExpirationMarkers().begin();
        EXPECT_EQ(savedValue.second[0], "2");*/
    }
}


#endif
