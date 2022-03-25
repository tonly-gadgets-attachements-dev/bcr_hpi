//
// Created by Administrator on 3/25/2022.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

extern "C" {
#include "bcr_mock.h"
}

class BCR_Cypd3177_Mock_Test:public testing::Test
{
protected:
    virtual void SetUp()
    {
//        std::cout<<"SetUp"<<std::endl;
        bcr_mock_create(regdata);
    }
    virtual void TearDown()
    {
//        std::cout<<"TearDown"<<std::endl;
    }
    uint8_t regdata[255] = {0};
    uint8_t input_data_4bytes[4] = {0x00, 0x01, 0x02, 0x03};
    uint8_t output_data_4bytes[4] = {0x00, 0x00, 0x00, 0x00};
};

TEST_F(BCR_Cypd3177_Mock_Test, ReturnNegativeOneWhenInputIsNull) {
    EXPECT_EQ(platform_write(NULL, 0, NULL, 1), -1);
}
TEST_F(BCR_Cypd3177_Mock_Test, ReturnNegativeOneWhenInputLengthIsZero) {
    EXPECT_EQ(platform_write(NULL, 0, input_data_4bytes, 0), -1);
}
TEST_F(BCR_Cypd3177_Mock_Test, Return0WhenInputIsNotEmptyNotNone) {
    EXPECT_EQ(platform_write(NULL, 0, input_data_4bytes, sizeof(input_data_4bytes)), 0);
}
TEST_F(BCR_Cypd3177_Mock_Test, ReadReturnNegativeOneWhenOutBufferIsNull) {
    EXPECT_EQ(platform_read(NULL, 0, NULL, 1), -1);
}
TEST_F(BCR_Cypd3177_Mock_Test, ReadReturnNegativeOneWhenOutBufferLengthIsZero) {
    uint8_t input[4] = {0};
    EXPECT_EQ(platform_read(input, 0, input, 0), -1);
}
TEST_F(BCR_Cypd3177_Mock_Test, WriteReadMatches) {
    platform_write(NULL, 0, input_data_4bytes, sizeof(input_data_4bytes));
    platform_read(NULL, 0, output_data_4bytes, sizeof(output_data_4bytes));
    EXPECT_THAT(std::vector<uint8_t>(input_data_4bytes, input_data_4bytes + 4),
            ::testing::ElementsAreArray(output_data_4bytes));
}
TEST_F(BCR_Cypd3177_Mock_Test, SpyLastRegisterMatches) {
    platform_write(NULL, 1, input_data_4bytes, sizeof(input_data_4bytes));
    EXPECT_EQ(1, bcr_spy_last_register());
}
TEST_F(BCR_Cypd3177_Mock_Test, SpyLasWriteDataMatches) {
    platform_write(NULL, 2, input_data_4bytes, sizeof(input_data_4bytes));
    EXPECT_THAT(std::vector<uint8_t>(regdata, regdata + 4),
            ::testing::ElementsAreArray(input_data_4bytes));
}
