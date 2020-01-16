#include <gtest/gtest.h>
#include "IMS_test.h"
#include "IMS_base.h"
#include "IMS_atalk.h"
#include "IMS_ftalk.h"
#include "IMS_mms.h"
#include "IMS_sms.h"

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