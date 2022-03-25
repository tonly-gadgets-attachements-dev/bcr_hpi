#include "gtest/gtest.h"
extern "C" {
#include "bcr_mock.h"
#include "bcr_hpi.h"
}
class BCR_Test:public testing::Test
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
    ctx_t ctx = {
            .write_reg = platform_write,
            .read_reg = platform_read,
            .handle = NULL
    };
};

TEST_F(BCR_Test, DeviceModeReturnsNegativeOnInvalidCtx)
{
    ctx_t ctx_invalid = {
            .write_reg = NULL,
            .read_reg = NULL,
            .handle = NULL
    };
    uint8_t mode = 0;
    EXPECT_EQ(-1, cypd3177_get_device_mode(&ctx_invalid, NULL));
    EXPECT_EQ(-1, cypd3177_get_device_mode(NULL, &mode));
    EXPECT_EQ(-1, cypd3177_get_device_mode(&ctx, NULL));
}

TEST_F(BCR_Test, DeviceModeReturn0andModeIs0x92OnSuccess) {
    uint8_t device_mode = 0;
    regdata[0] = 0x92;
    cypd3177_get_device_mode(&ctx, &device_mode);
    EXPECT_EQ(0x92, device_mode);
}
