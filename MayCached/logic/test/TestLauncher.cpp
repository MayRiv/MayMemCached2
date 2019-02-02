#include "gtest/gtest.h"
//#include "TimeExpirationManagerTest.hpp"
#include "TimeExpirationCoreTest.hpp"
#include "DatabaseMarshallerTest.hpp"
int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
