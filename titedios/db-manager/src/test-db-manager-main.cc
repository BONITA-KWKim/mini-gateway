#include "db-manager-main.h"
#include <gtest/gtest.h>

TEST(IAS_test, test001) 
{
  EXPECT_EQ(2, (1+1));
}

int main (int argc, char *argv[]) 
{
    std::cout << COUT_PREFIX << "DB manage test module\n"; 
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
