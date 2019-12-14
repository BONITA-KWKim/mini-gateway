#include "internal_API_server.h"
#include "gtest/gtest.h"

TEST(IAS_test, test001) 
{
  EXPECT_EQ(2, (1+1));
}

int main(int argc, char *argv[]) 
{
    printf("Hello interanp API server test.\n");
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}