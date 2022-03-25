//
// Created by Administrator on 3/25/2022.
//

#include "bcr_hpi.h"

int32_t cypd3177_get_device_mode(ctx_t *ctx, uint8_t *mode) {
    if (!ctx || !ctx->write_reg || !ctx->read_reg || !mode) {
        return -1;
    }

    return ctx->read_reg(ctx->handle, DEVICE_MODE_REG, mode, 1);
}

int32_t cypd3177_get_silicon_id(ctx_t *ctx, uint16_t *id) {
    if (!ctx || !ctx->write_reg || !ctx->read_reg || !id) {
        return -1;
    }
    uint8_t data[2] = {0};
    int32_t ret = ctx->read_reg(ctx->handle, SILICON_ID_REG, data, 2);
    if (ret < 0) {
        return ret;
    } else {
        *id = (data[0] << 8) | data[1];
        return ret;
    }
}
