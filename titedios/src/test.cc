#include "test.h"

TEST(test_case, test001) {
  EXPECT_EQ(2, (1+1));
}

int main(int argc, char *argv[]){
    printf("Hello mini gateway!\n");
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}