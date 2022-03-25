//
// Created by Administrator on 3/25/2022.
//

#include "bcr_hpi.h"

int32_t cypd3177_get_device_mode(ctx_t *ctx, uint8_t *mode) {
    if (!ctx || !ctx->write_reg || !ctx->read_reg || !mode) {
        return -1;
    }
    return 0;
}
