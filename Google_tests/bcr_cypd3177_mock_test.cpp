//
// Created by Administrator on 3/25/2022.
//

#include "gtest/gtest.h"

extern "C" {
#include "bcr_mock.h"
}

class BCR_Cypd3177_Mock_Test:public testing::Test
{
protected:
    virtual void SetUp()
    {
//        std::cout<<"SetUp"<<std::endl;
    }
    virtual void TearDown()
    {
//        std::cout<<"TearDown"<<std::endl;
    }
};

TEST_F(BCR_Cypd3177_Mock_Test, ReturnNegativeOneWhenInputIsNull) {
    EXPECT_EQ(platform_write(NULL, 0, NULL, 1), -1);
}
TEST_F(BCR_Cypd3177_Mock_Test, ReturnNegativeOneWhenInputLengthIsZero) {
    uint8_t input[4] = {0};
    EXPECT_EQ(platform_write(input, 0, input, 0), -1);
}
TEST_F(BCR_Cypd3177_Mock_Test, Return0WhenInputIsNotEmptyNotNone) {
    uint8_t input[4] = {0};
    EXPECT_EQ(platform_write(NULL, 0, input, sizeof(input)), 0);
}
TEST_F(BCR_Cypd3177_Mock_Test, ReadReturnNegativeOneWhenOutBufferIsNull) {
    EXPECT_EQ(platform_read(NULL, 0, NULL, 1), -1);
}
TEST_F(BCR_Cypd3177_Mock_Test, ReadReturnNegativeOneWhenOutBufferLengthIsZero) {
    uint8_t input[4] = {0};
    EXPECT_EQ(platform_read(input, 0, input, 0), -1);
}
