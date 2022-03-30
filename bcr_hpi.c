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

int32_t cypd3177_get_device_interrupt(ctx_t *ctx, uint8_t *device_int) {
    if (!ctx || !ctx->write_reg || !ctx->read_reg || !device_int) {
        return -1;
    }
    interrupt_reg_t interrupt_reg;
    int32_t ret = ctx->read_reg(ctx->handle, INTERRUPT_REG, (uint8_t *)&interrupt_reg, 1);
    if (ret < 0) {
        return ret;
    } else {
        *device_int = interrupt_reg.device_interrupt;
        return ret;
    }
}

int32_t cypd3177_get_pd_interrupt(ctx_t *ctx, uint8_t *pd_int) {
    if (!ctx || !ctx->write_reg || !ctx->read_reg || !pd_int) {
        return -1;
    }
    interrupt_reg_t interrupt_reg;
    int32_t ret = ctx->read_reg(ctx->handle, INTERRUPT_REG, (uint8_t *)&interrupt_reg, 1);
    if (ret < 0) {
        return ret;
    } else {
        *pd_int = interrupt_reg.pd_port_interrupt;
        return ret;
    }
}

int32_t cypd3177_get_default_config(ctx_t *ctx, uint8_t *pd_status){
    if (!ctx || !ctx->write_reg || !ctx->read_reg || !pd_status) {
        return -1;
    }
    pd_status_reg_t pd_status_reg;
    int32_t ret = ctx->read_reg(ctx->handle, PD_STATUS_REG, (uint8_t *)&pd_status_reg, 4);
    if (ret < 0) {
        return ret;
    } else {
        *pd_status = pd_status_reg.defaul_cfg;
        return ret;
    }
}

int32_t cypd3177_get_cur_port_data_role(ctx_t *ctx, uint8_t *pd_status) {
    if (!ctx || !ctx->write_reg || !ctx->read_reg || !pd_status) {
        return -1;
    }
    pd_status_reg_t pd_status_reg;
    int32_t ret = ctx->read_reg(ctx->handle, PD_STATUS_REG, (uint8_t *)&pd_status_reg, 4);
    if ((ret < 0) || (pd_status_reg.contract_state == 0)) {
        ret = -1;
        return ret;
    } else {
        *pd_status = pd_status_reg.current_port_data_role;
        return ret;
    }
}

int32_t cypd3177_get_cur_port_power_role(ctx_t *ctx, uint8_t *pd_status) {
    if (!ctx || !ctx->write_reg || !ctx->read_reg || !pd_status) {
        return -1;
    }
    pd_status_reg_t pd_status_reg;
    int32_t ret = ctx->read_reg(ctx->handle, PD_STATUS_REG, (uint8_t *)&pd_status_reg, 4);
    if ((ret < 0) || (pd_status_reg.contract_state == 0)) {
        ret = -1;
        return ret;
    } else {
        *pd_status = pd_status_reg.current_port_power_role;
        return ret;
    }
}

int32_t cypd3177_get_contract_state(ctx_t *ctx, uint8_t *pd_status) {
    if (!ctx || !ctx->write_reg || !ctx->read_reg || !pd_status) {
        return -1;
    }
    pd_status_reg_t pd_status_reg;
    int32_t ret = ctx->read_reg(ctx->handle, PD_STATUS_REG, (uint8_t *)&pd_status_reg, 4);
    if (ret < 0) {
        return ret;
    } else {
        *pd_status = pd_status_reg.contract_state;
        return ret;
    }
}

int32_t cypd3177_get_rp_state(ctx_t *ctx, uint8_t *pd_status) {
    if (!ctx || !ctx->write_reg || !ctx->read_reg || !pd_status) {
        return -1;
    }
    pd_status_reg_t pd_status_reg;
    int32_t ret = ctx->read_reg(ctx->handle, PD_STATUS_REG, (uint8_t *)&pd_status_reg, 4);
    if ((ret < 0) || (pd_status_reg.contract_state == 0)) {
        ret = -1;
        return ret;
    } else {
        *pd_status = pd_status_reg.rp_state;
        return ret;
    }
}

int32_t cypd3177_get_policy_engine_state(ctx_t *ctx, uint8_t *pd_status) {
    if (!ctx || !ctx->write_reg || !ctx->read_reg || !pd_status) {
        return -1;
    }
    pd_status_reg_t pd_status_reg;
    int32_t ret = ctx->read_reg(ctx->handle, PD_STATUS_REG, (uint8_t *)&pd_status_reg, 4);
    if ((ret < 0) || (pd_status_reg.contract_state == 0)) {
        ret = -1;
        return ret;
    } else {
        *pd_status = pd_status_reg.policy_engine_state;
        return ret;
    }
}

int32_t cypd3177_get_pd_spec_ver(ctx_t *ctx, uint8_t *pd_status) {
    if (!ctx || !ctx->write_reg || !ctx->read_reg || !pd_status) {
        return -1;
    }
    pd_status_reg_t pd_status_reg;
    int32_t ret = ctx->read_reg(ctx->handle, PD_STATUS_REG, (uint8_t *)&pd_status_reg, 4);
    if ((ret < 0) || (pd_status_reg.contract_state == 0)) {
        ret = -1;
        return ret;
    } else {
        *pd_status = pd_status_reg.pd_spec_ver;
        return ret;
    }
}

int32_t cypd3177_get_partner_pd_spec_ver(ctx_t *ctx, uint8_t *pd_status) {
    if (!ctx || !ctx->write_reg || !ctx->read_reg || !pd_status) {
        return -1;
    }
    pd_status_reg_t pd_status_reg;
    int32_t ret = ctx->read_reg(ctx->handle, PD_STATUS_REG, (uint8_t *)&pd_status_reg, 4);
    if ((ret < 0) || (pd_status_reg.contract_state == 0)) {
        ret = -1;
        return ret;
    } else {
        *pd_status = pd_status_reg.partner_pd_spec_ver;
        return ret;
    }
}

int32_t cypd3177_get_partner_unchunked_msg_spt_status(ctx_t *ctx, uint8_t *pd_status) {
    if (!ctx || !ctx->write_reg || !ctx->read_reg || !pd_status) {
        return -1;
    }
    pd_status_reg_t pd_status_reg;
    int32_t ret = ctx->read_reg(ctx->handle, PD_STATUS_REG, (uint8_t *)&pd_status_reg, 4);
    if ((ret < 0) || (pd_status_reg.contract_state == 0)) {
        ret = -1;
        return ret;
    } else {
        *pd_status = pd_status_reg.partner_unchunked_msg_spt_status;
        return ret;
    }
}
