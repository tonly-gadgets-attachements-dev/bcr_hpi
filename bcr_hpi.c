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

int32_t cypd3177_get_device_interrupt(ctx_t *ctx, dev_or_pd_int_e *device_int) {
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

int32_t cypd3177_get_pd_interrupt(ctx_t *ctx, dev_or_pd_int_e *pd_int) {
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

int32_t cypd3177_get_default_config(ctx_t *ctx, uint8_t *df_cfg){
    if (!ctx || !ctx->write_reg || !ctx->read_reg || !df_cfg) {
        return -1;
    }
    pd_status_reg_t pd_status_reg;
    int32_t ret = ctx->read_reg(ctx->handle, PD_STATUS_REG, (uint8_t *)&pd_status_reg, 4);
    if (ret < 0) {
        return ret;
    } else {
        *df_cfg = pd_status_reg.defaul_cfg;
        return ret;
    }
}

int32_t cypd3177_get_cur_port_data_role(ctx_t *ctx, current_port_data_role_e *data_role) {
    if (!ctx || !ctx->write_reg || !ctx->read_reg || !data_role) {
        return -1;
    }
    pd_status_reg_t pd_status_reg;
    int32_t ret = ctx->read_reg(ctx->handle, PD_STATUS_REG, (uint8_t *)&pd_status_reg, 4);
    if ((ret < 0) || (pd_status_reg.contract_state == not_exist)) {
        ret = -1;
        return ret;
    } else {
        *data_role = pd_status_reg.current_port_data_role;
        return ret;
    }
}

int32_t cypd3177_get_cur_port_power_role(ctx_t *ctx, uint8_t *pwr_role) {
    if (!ctx || !ctx->write_reg || !ctx->read_reg || !pwr_role) {
        return -1;
    }
    pd_status_reg_t pd_status_reg;
    int32_t ret = ctx->read_reg(ctx->handle, PD_STATUS_REG, (uint8_t *)&pd_status_reg, 4);
    if ((ret < 0) || (pd_status_reg.contract_state == not_exist)) {
        ret = -1;
        return ret;
    } else {
        *pwr_role = pd_status_reg.current_port_power_role;
        return ret;
    }
}

int32_t cypd3177_get_contract_state(ctx_t *ctx, contract_state_e *contract_state) {
    if (!ctx || !ctx->write_reg || !ctx->read_reg || !contract_state) {
        return -1;
    }
    pd_status_reg_t pd_status_reg;
    int32_t ret = ctx->read_reg(ctx->handle, PD_STATUS_REG, (uint8_t *)&pd_status_reg, 4);
    if (ret < 0) {
        return ret;
    } else {
        *contract_state = pd_status_reg.contract_state;
        return ret;
    }
}

int32_t cypd3177_get_rp_state(ctx_t *ctx, rp_state_e *rp_state) {
    if (!ctx || !ctx->write_reg || !ctx->read_reg || !rp_state) {
        return -1;
    }
    pd_status_reg_t pd_status_reg;
    int32_t ret = ctx->read_reg(ctx->handle, PD_STATUS_REG, (uint8_t *)&pd_status_reg, 4);
    if ((ret < 0) || (pd_status_reg.contract_state == not_exist)) {
        ret = -1;
        return ret;
    } else {
        *rp_state = pd_status_reg.rp_state;
        return ret;
    }
}

int32_t cypd3177_get_policy_engine_state(ctx_t *ctx, policy_engine_state_e *pe_state) {
    if (!ctx || !ctx->write_reg || !ctx->read_reg || !pe_state) {
        return -1;
    }
    pd_status_reg_t pd_status_reg;
    int32_t ret = ctx->read_reg(ctx->handle, PD_STATUS_REG, (uint8_t *)&pd_status_reg, 4);
    if ((ret < 0) || (pd_status_reg.contract_state == not_exist)) {
        ret = -1;
        return ret;
    } else {
        *pe_state = pd_status_reg.policy_engine_state;
        return ret;
    }
}

int32_t cypd3177_get_pd_spec_ver(ctx_t *ctx, pd_spec_ver_e *pd_ver) {
    if (!ctx || !ctx->write_reg || !ctx->read_reg || !pd_ver) {
        return -1;
    }
    pd_status_reg_t pd_status_reg;
    int32_t ret = ctx->read_reg(ctx->handle, PD_STATUS_REG, (uint8_t *)&pd_status_reg, 4);
    if ((ret < 0) || (pd_status_reg.contract_state == not_exist)) {
        ret = -1;
        return ret;
    } else {
        *pd_ver = pd_status_reg.pd_spec_ver;
        return ret;
    }
}

int32_t cypd3177_get_partner_pd_spec_ver(ctx_t *ctx, pd_spec_ver_e *pd_ver) {
    if (!ctx || !ctx->write_reg || !ctx->read_reg || !pd_ver) {
        return -1;
    }
    pd_status_reg_t pd_status_reg;
    int32_t ret = ctx->read_reg(ctx->handle, PD_STATUS_REG, (uint8_t *)&pd_status_reg, 4);
    if ((ret < 0) || (pd_status_reg.contract_state == not_exist)) {
        ret = -1;
        return ret;
    } else {
        *pd_ver = pd_status_reg.partner_pd_spec_ver;
        return ret;
    }
}

int32_t cypd3177_get_partner_unchunked_msg_spt_status(ctx_t *ctx, partner_unchunked_msg_spt_status_e *msg_spt_state) {
    if (!ctx || !ctx->write_reg || !ctx->read_reg || !msg_spt_state) {
        return -1;
    }
    pd_status_reg_t pd_status_reg;
    int32_t ret = ctx->read_reg(ctx->handle, PD_STATUS_REG, (uint8_t *)&pd_status_reg, 4);
    if ((ret < 0) || (pd_status_reg.contract_state == not_exist)) {
        ret = -1;
        return ret;
    } else {
        *msg_spt_state = pd_status_reg.partner_unchunked_msg_spt_status;
        return ret;
    }
}

int32_t cypd3177_get_partner_conn_status(ctx_t *ctx, partner_conn_status_e *conn_status) {
    if (!ctx || !ctx->write_reg || !ctx->read_reg || !conn_status) {
        return -1;
    }
    typec_status_reg_t typec_status_reg;
    int32_t ret = ctx->read_reg(ctx->handle, TYPE_C_STATUS_REG, (uint8_t *)&typec_status_reg, 1);
    if (ret < 0) {
        return ret;
    } else {
        *conn_status = typec_status_reg.partner_conn_status;
        return ret;
    }
}

int32_t cypd3177_get_cc_polarity(ctx_t *ctx, cc_polarity_e *cc_polarity) {
    if (!ctx || !ctx->write_reg || !ctx->read_reg || !cc_polarity) {
        return -1;
    }
    typec_status_reg_t typec_status_reg;
    int32_t ret = ctx->read_reg(ctx->handle, TYPE_C_STATUS_REG, (uint8_t *)&typec_status_reg, 1);
    if ((ret < 0) || (typec_status_reg.partner_conn_status == not_connected)) {
        ret = -1;
        return ret;
    } else {
        *cc_polarity = typec_status_reg.cc_polarity;
        return ret;
    }
}

int32_t cypd3177_get_attached_dev_type(ctx_t *ctx, attached_dev_type_e *dev_type) {
    if (!ctx || !ctx->write_reg || !ctx->read_reg || !dev_type) {
        return -1;
    }
    typec_status_reg_t typec_status_reg;
    int32_t ret = ctx->read_reg(ctx->handle, TYPE_C_STATUS_REG, (uint8_t *)&typec_status_reg, 1);
    if ((ret < 0) || (typec_status_reg.partner_conn_status == not_connected)) {
        ret = -1;
        return ret;
    } else {
        *dev_type = typec_status_reg.attached_dev_type;
        return ret;
    }
}

int32_t cypd3177_get_typec_cur_lvl(ctx_t *ctx, typec_cur_lvl_e *cur_lvl) {
    if (!ctx || !ctx->write_reg || !ctx->read_reg || !cur_lvl) {
        return -1;
    }
    typec_status_reg_t typec_status_reg;
    int32_t ret = ctx->read_reg(ctx->handle, TYPE_C_STATUS_REG, (uint8_t *)&typec_status_reg, 1);
    if ((ret < 0) || (typec_status_reg.partner_conn_status == not_connected)) {
        ret = -1;
        return ret;
    } else {
        *cur_lvl = typec_status_reg.typec_cur_lvl;
        return ret;
    }
}

int32_t cypd3177_get_vbus_vol(ctx_t *ctx, uint16_t *vol) {
    if (!ctx || !ctx->write_reg || !ctx->read_reg || !vol) {
        return -1;
    }
    uint16_t voltage;
    int32_t ret = ctx->read_reg(ctx->handle, BUS_VOLTAGE_REG, (uint8_t *)&voltage, 1);
    if (ret < 0) {
        return ret;
    } else {
        *vol = voltage * 100;
        return ret;
    }
}
