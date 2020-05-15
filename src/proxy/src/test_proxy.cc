#include "proxy.hh"
#include "gtest/gtest.h"

TEST(proxy_test, test001) {
  EXPECT_EQ(2, (1+1));
}

int main(int argc, char *argv[]) {
    printf("Hello gw proxy\n");
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}