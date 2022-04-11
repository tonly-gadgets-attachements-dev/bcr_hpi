#include "gtest/gtest.h"
extern "C"
{
#include "bcr_mock.h"
#include "bcr_hpi.h"
}
class BCR_Test : public testing::Test
{
protected:
    void SetUp() override
    {
        //        std::cout<<"SetUp"<<std::endl;
        bcr_mock_create(regdata);
    }
    void TearDown() override
    {
        //        std::cout<<"TearDown"<<std::endl;
    }
    uint8_t regdata[255] = {0};
    uint8_t input_data_4bytes[4] = {0x00, 0x01, 0x02, 0x03};
    uint8_t output_data_4bytes[4] = {0x00, 0x00, 0x00, 0x00};
    ctx_t ctx = {
        .write_reg = platform_write,
        .read_reg = platform_read,
        .handle = nullptr};
};

TEST_F(BCR_Test, DeviceModeReturnsNegativeOnInvalidCtx)
{
    ctx_t ctx_invalid = {
        .write_reg = nullptr,
        .read_reg = nullptr,
        .handle = nullptr};
    uint8_t mode = 0;
    EXPECT_EQ(-1, cypd3177_get_device_mode(&ctx_invalid, nullptr));
    EXPECT_EQ(-1, cypd3177_get_device_mode(nullptr, &mode));
    EXPECT_EQ(-1, cypd3177_get_device_mode(&ctx, nullptr));
}

TEST_F(BCR_Test, DeviceModeReturn0andModeIs0x92OnSuccess)
{
    uint8_t device_mode = 0;
    regdata[0] = 0x92;
    cypd3177_get_device_mode(&ctx, &device_mode);
    EXPECT_EQ(0x92, device_mode);
    EXPECT_EQ(DEVICE_MODE_REG, bcr_spy_last_register());
}

TEST_F(BCR_Test, SiliconIDReturnsNegativeOnInvalidInputs)
{
    ctx_t ctx_invalid = {
        .write_reg = nullptr,
        .read_reg = nullptr,
        .handle = nullptr};
    uint16_t mode = 0;
    EXPECT_EQ(-1, cypd3177_get_silicon_id(&ctx_invalid, nullptr));
    EXPECT_EQ(-1, cypd3177_get_silicon_id(nullptr, &mode));
    EXPECT_EQ(-1, cypd3177_get_silicon_id(&ctx, nullptr));
}
TEST_F(BCR_Test, SiliconIDReturns0x11B0OnSuccess)
{
    uint16_t device_mode = 0;
    regdata[0] = 0x11;
    regdata[1] = 0xB0;
    cypd3177_get_silicon_id(&ctx, &device_mode);
    EXPECT_EQ(0x11B0, device_mode);
    EXPECT_EQ(SILICON_ID_REG, bcr_spy_last_register());
}

TEST_F(BCR_Test, DeviceInterruptStatusReturnsNegativeOnInvalidInputs)
{
    ctx_t ctx_invalid = {
        .write_reg = nullptr,
        .read_reg = nullptr,
        .handle = nullptr};
    dev_or_pd_int_e mode = no_int;
    EXPECT_EQ(-1, cypd3177_get_device_interrupt(&ctx_invalid, nullptr));
    EXPECT_EQ(-1, cypd3177_get_device_interrupt(nullptr, &mode));
    EXPECT_EQ(-1, cypd3177_get_device_interrupt(&ctx, nullptr));
}
TEST_F(BCR_Test, DeviceInterruptPendingReturns0x00)
{
    dev_or_pd_int_e interrupt = no_int;
    regdata[0] = 0x01;
    int32_t ret = cypd3177_get_device_interrupt(&ctx, &interrupt);
    EXPECT_EQ(0x01, interrupt);
    EXPECT_EQ(0x0, ret);
    EXPECT_EQ(INTERRUPT_REG, bcr_spy_last_register());
}
TEST_F(BCR_Test, DeviceInterruptClearReturns0x00)
{
    dev_or_pd_int_e interrupt = no_int;
    regdata[0] = 0x00;
    int32_t ret = cypd3177_get_device_interrupt(&ctx, &interrupt);
    EXPECT_EQ(0x00, interrupt);
    EXPECT_EQ(0x0, ret);
    EXPECT_EQ(INTERRUPT_REG, bcr_spy_last_register());
}

TEST_F(BCR_Test, PDInterruptStatusReturnsNegativeOnInvalidInputs)
{
    ctx_t ctx_invalid = {
        .write_reg = nullptr,
        .read_reg = nullptr,
        .handle = nullptr};
    dev_or_pd_int_e pd_int = no_int;
    EXPECT_EQ(-1, cypd3177_get_pd_interrupt(&ctx_invalid, nullptr));
    EXPECT_EQ(-1, cypd3177_get_pd_interrupt(nullptr, &pd_int));
    EXPECT_EQ(-1, cypd3177_get_pd_interrupt(&ctx, nullptr));
}
TEST_F(BCR_Test, PDInterruptPendingReturns0x00)
{
    dev_or_pd_int_e interrupt = no_int;
    regdata[0] = 0x03;
    int32_t ret = cypd3177_get_pd_interrupt(&ctx, &interrupt);
    EXPECT_EQ(0x01, interrupt);
    EXPECT_EQ(0x0, ret);
    EXPECT_EQ(INTERRUPT_REG, bcr_spy_last_register());
}
TEST_F(BCR_Test, PDInterruptClearReturns0x00)
{
    dev_or_pd_int_e interrupt = no_int;
    regdata[0] = 0x00;
    int32_t ret = cypd3177_get_pd_interrupt(&ctx, &interrupt);
    EXPECT_EQ(0x00, interrupt);
    EXPECT_EQ(0x0, ret);
    EXPECT_EQ(INTERRUPT_REG, bcr_spy_last_register());
}

TEST_F(BCR_Test, DefaultConfigReturnsNegativeOnInvalidInputs)
{
    ctx_t ctx_invalid = {
        .write_reg = nullptr,
        .read_reg = nullptr,
        .handle = nullptr};
    uint8_t pd_status = 0;
    EXPECT_EQ(-1, cypd3177_get_default_config(&ctx_invalid, nullptr));
    EXPECT_EQ(-1, cypd3177_get_default_config(nullptr, &pd_status));
    EXPECT_EQ(-1, cypd3177_get_default_config(&ctx, nullptr));
}
TEST_F(BCR_Test, DefaultConfigReturns0x00OnSuccess)
{
    uint8_t pd_status = 0;
    regdata[0] = 0x00;
    int32_t ret = cypd3177_get_default_config(&ctx, &pd_status);
    EXPECT_EQ(0x00, pd_status);
    EXPECT_EQ(0x0, ret);
    EXPECT_EQ(PD_STATUS_REG, bcr_spy_last_register());
}

TEST_F(BCR_Test, CurPortDataRoleReturnsNegativeOnInvalidInputs)
{
    ctx_t ctx_invalid = {
        .write_reg = nullptr,
        .read_reg = nullptr,
        .handle = nullptr};
    current_port_data_role_e pd_status = ufp;
    EXPECT_EQ(-1, cypd3177_get_cur_port_data_role(&ctx_invalid, nullptr));
    EXPECT_EQ(-1, cypd3177_get_cur_port_data_role(nullptr, &pd_status));
    EXPECT_EQ(-1, cypd3177_get_cur_port_data_role(&ctx, nullptr));
}
TEST_F(BCR_Test, CurPortDataRoleReturns0x00OnSuccess)
{
    current_port_data_role_e pd_status = ufp;
    regdata[0] = 0x00;
    regdata[1] = 0x04;
    int32_t ret = cypd3177_get_cur_port_data_role(&ctx, &pd_status);
    EXPECT_EQ(0x00, pd_status);
    EXPECT_EQ(0x0, ret);
    EXPECT_EQ(PD_STATUS_REG, bcr_spy_last_register());
}
TEST_F(BCR_Test, CurPortDataRoleReturns0x01OnSuccess)
{
    current_port_data_role_e pd_status = ufp;
    regdata[0] = 0x40;
    regdata[1] = 0x04;
    int32_t ret = cypd3177_get_cur_port_data_role(&ctx, &pd_status);
    EXPECT_EQ(0x01, pd_status);
    EXPECT_EQ(0x0, ret);
    EXPECT_EQ(PD_STATUS_REG, bcr_spy_last_register());
}
TEST_F(BCR_Test, CurPortDataRoleReturnsNegativeOnFail)
{
    current_port_data_role_e pd_status = ufp;
    regdata[0] = 0x00;
    regdata[1] = 0x00;
    int32_t ret = cypd3177_get_cur_port_data_role(&ctx, &pd_status);
    EXPECT_EQ(0x00, pd_status);
    EXPECT_EQ(-1, ret);
    EXPECT_EQ(PD_STATUS_REG, bcr_spy_last_register());
}

TEST_F(BCR_Test, CcPolaarityReturnsNegativeOnInvalidInputs)
{
    ctx_t ctx_invalid = {
        .write_reg = nullptr,
        .read_reg = nullptr,
        .handle = nullptr};
    cc_polarity_e type_c_status = cc1;
    EXPECT_EQ(-1, cypd3177_get_cc_polarity(&ctx_invalid, nullptr));
    EXPECT_EQ(-1, cypd3177_get_cc_polarity(nullptr, &type_c_status));
    EXPECT_EQ(-1, cypd3177_get_cc_polarity(&ctx, nullptr));
}
TEST_F(BCR_Test, CcPolaarityReturns0x00OnSuccess)
{
    cc_polarity_e type_c_status = cc1;
    regdata[0] = 0x01;
    int32_t ret = cypd3177_get_cc_polarity(&ctx, &type_c_status);
    EXPECT_EQ(0x00, type_c_status);
    EXPECT_EQ(0x0, ret);
    EXPECT_EQ(TYPE_C_STATUS_REG, bcr_spy_last_register());
}
TEST_F(BCR_Test, CcPolaarityReturns0x01OnSuccess)
{
    cc_polarity_e type_c_status = cc1;
    regdata[0] = 0x03;
    int32_t ret = cypd3177_get_cc_polarity(&ctx, &type_c_status);
    EXPECT_EQ(0x01, type_c_status);
    EXPECT_EQ(0x0, ret);
    EXPECT_EQ(TYPE_C_STATUS_REG, bcr_spy_last_register());
}
TEST_F(BCR_Test, CcPolaarityReturnsNegativeOnFail)
{
    cc_polarity_e type_c_status = cc1;
    regdata[0] = 0x00;
    int32_t ret = cypd3177_get_cc_polarity(&ctx, &type_c_status);
    EXPECT_EQ(0x00, type_c_status);
    EXPECT_EQ(-1, ret);
    EXPECT_EQ(TYPE_C_STATUS_REG, bcr_spy_last_register());
}