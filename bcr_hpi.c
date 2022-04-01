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

int32_t cypd3177_get_cur_pdo(ctx_t *ctx, uint32_t *pdo) {
    if (!ctx || !ctx->write_reg || !ctx->read_reg || !pdo) {
        return -1;
    }
    uint32_t cur_pdo;
    int32_t ret = ctx->read_reg(ctx->handle, CURRENT_PDO_REG, (uint8_t *)&cur_pdo, 4);
    if (ret < 0) {
        return ret;
    } else {
        *pdo = cur_pdo;
        return ret;
    }
}

int32_t cypd3177_get_cur_rdo(ctx_t *ctx, uint32_t *rdo) {
    if (!ctx || !ctx->write_reg || !ctx->read_reg || !rdo) {
        return -1;
    }
    uint32_t cur_rdo;
    int32_t ret = ctx->read_reg(ctx->handle, CURRENT_RDO_REG, (uint8_t *)&cur_rdo, 4);
    if (ret < 0) {
        return ret;
    } else {
        *rdo = cur_rdo;
        return ret;
    }
}

int32_t cypd3177_get_de_swap_response(ctx_t *ctx, response_type_e *dr_swap_resp) {
    if (!ctx || !ctx->write_reg || !ctx->read_reg || !dr_swap_resp) {
        return -1;
    }
    swap_response_reg_t swap_response;
    int32_t ret = ctx->read_reg(ctx->handle, SWAP_RESPONSE_REG, (uint8_t *)&swap_response, 1);
    if (ret < 0) {
        return ret;
    } else {
        *dr_swap_resp = swap_response.dr_swap_response;
        return ret;
    }
}

int32_t cypd3177_get_vconn_swap_response(ctx_t *ctx, response_type_e *vconn_swap_resp) {
    if (!ctx || !ctx->write_reg || !ctx->read_reg || !vconn_swap_resp) {
        return -1;
    }
    swap_response_reg_t swap_response;
    int32_t ret = ctx->read_reg(ctx->handle, SWAP_RESPONSE_REG, (uint8_t *)&swap_response, 1);
    if (ret < 0) {
        return ret;
    } else {
        *vconn_swap_resp = swap_response.vconn_swap_response;
        return ret;
    }
}

int32_t cypd3177_check_is_typec_dev_attached(ctx_t *ctx, event_state_e *state) {
    if (!ctx || !ctx->write_reg || !ctx->read_reg || !state) {
        return -1;
    }
    event_status_reg_t event_status;
    int32_t ret = ctx->read_reg(ctx->handle, EVENT_STATUS_REG, (uint8_t *)&event_status, 4);
    if (ret < 0) {
        return ret;
    } else {
        *state = event_status.typec_dev_attached;
        return ret;
    }
}

int32_t cypd3177_check_is_typec_dev_disconnected(ctx_t *ctx, event_state_e *state) {
    if (!ctx || !ctx->write_reg || !ctx->read_reg || !state) {
        return -1;
    }
    event_status_reg_t event_status;
    int32_t ret = ctx->read_reg(ctx->handle, EVENT_STATUS_REG, (uint8_t *)&event_status, 4);
    if (ret < 0) {
        return ret;
    } else {
        *state = event_status.typec_dev_disconnected;
        return ret;
    }
}

int32_t cypd3177_check_is_pd_contract_nego_completed(ctx_t *ctx, event_state_e *state) {
    if (!ctx || !ctx->write_reg || !ctx->read_reg || !state) {
        return -1;
    }
    event_status_reg_t event_status;
    int32_t ret = ctx->read_reg(ctx->handle, EVENT_STATUS_REG, (uint8_t *)&event_status, 4);
    if (ret < 0) {
        return ret;
    } else {
        *state = event_status.pd_contract_nego_completed;
        return ret;
    }
}

int32_t cypd3177_check_is_power_role_swap_completed(ctx_t *ctx, event_state_e *state) {
    if (!ctx || !ctx->write_reg || !ctx->read_reg || !state) {
        return -1;
    }
    event_status_reg_t event_status;
    int32_t ret = ctx->read_reg(ctx->handle, EVENT_STATUS_REG, (uint8_t *)&event_status, 4);
    if (ret < 0) {
        return ret;
    } else {
        *state = event_status.power_role_swap_completed;
        return ret;
    }
}

int32_t cypd3177_check_is_data_role_swap_completed(ctx_t *ctx, event_state_e *state) {
    if (!ctx || !ctx->write_reg || !ctx->read_reg || !state) {
        return -1;
    }
    event_status_reg_t event_status;
    int32_t ret = ctx->read_reg(ctx->handle, EVENT_STATUS_REG, (uint8_t *)&event_status, 4);
    if (ret < 0) {
        return ret;
    } else {
        *state = event_status.data_role_swap_completed;
        return ret;
    }
}

int32_t cypd3177_check_is_vconn_swap_completed(ctx_t *ctx, event_state_e *state) {
    if (!ctx || !ctx->write_reg || !ctx->read_reg || !state) {
        return -1;
    }
    event_status_reg_t event_status;
    int32_t ret = ctx->read_reg(ctx->handle, EVENT_STATUS_REG, (uint8_t *)&event_status, 4);
    if (ret < 0) {
        return ret;
    } else {
        *state = event_status.vconn_swap_completed;
        return ret;
    }
}

int32_t cypd3177_check_is_hard_reset_received(ctx_t *ctx, event_state_e *state) {
    if (!ctx || !ctx->write_reg || !ctx->read_reg || !state) {
        return -1;
    }
    event_status_reg_t event_status;
    int32_t ret = ctx->read_reg(ctx->handle, EVENT_STATUS_REG, (uint8_t *)&event_status, 4);
    if (ret < 0) {
        return ret;
    } else {
        *state = event_status.hard_reset_received;
        return ret;
    }
}

int32_t cypd3177_check_is_hard_reset_sent(ctx_t *ctx, event_state_e *state) {
    if (!ctx || !ctx->write_reg || !ctx->read_reg || !state) {
        return -1;
    }
    event_status_reg_t event_status;
    int32_t ret = ctx->read_reg(ctx->handle, EVENT_STATUS_REG, (uint8_t *)&event_status, 4);
    if (ret < 0) {
        return ret;
    } else {
        *state = event_status.hard_reset_sent;
        return ret;
    }
}

int32_t cypd3177_check_is_soft_reset_sent(ctx_t *ctx, event_state_e *state) {
    if (!ctx || !ctx->write_reg || !ctx->read_reg || !state) {
        return -1;
    }
    event_status_reg_t event_status;
    int32_t ret = ctx->read_reg(ctx->handle, EVENT_STATUS_REG, (uint8_t *)&event_status, 4);
    if (ret < 0) {
        return ret;
    } else {
        *state = event_status.soft_reset_sent;
        return ret;
    }
}

int32_t cypd3177_check_is_cable_reset_sent(ctx_t *ctx, event_state_e *state) {
    if (!ctx || !ctx->write_reg || !ctx->read_reg || !state) {
        return -1;
    }
    event_status_reg_t event_status;
    int32_t ret = ctx->read_reg(ctx->handle, EVENT_STATUS_REG, (uint8_t *)&event_status, 4);
    if (ret < 0) {
        return ret;
    } else {
        *state = event_status.cable_reset_sent;
        return ret;
    }
}

int32_t cypd3177_check_is_typec_err_recovery_initiated(ctx_t *ctx, event_state_e *state) {
    if (!ctx || !ctx->write_reg || !ctx->read_reg || !state) {
        return -1;
    }
    event_status_reg_t event_status;
    int32_t ret = ctx->read_reg(ctx->handle, EVENT_STATUS_REG, (uint8_t *)&event_status, 4);
    if (ret < 0) {
        return ret;
    } else {
        *state = event_status.typec_err_recovery_initiated;
        return ret;
    }
}

int32_t cypd3177_check_is_bcr_entered_src_disabled_state(ctx_t *ctx, event_state_e *state) {
    if (!ctx || !ctx->write_reg || !ctx->read_reg || !state) {
        return -1;
    }
    event_status_reg_t event_status;
    int32_t ret = ctx->read_reg(ctx->handle, EVENT_STATUS_REG, (uint8_t *)&event_status, 4);
    if (ret < 0) {
        return ret;
    } else {
        *state = event_status.bcr_entered_source_disabled_state;
        return ret;
    }
}

int32_t cypd3177_check_is_unexpected_volt_on_vbus(ctx_t *ctx, event_state_e *state) {
    if (!ctx || !ctx->write_reg || !ctx->read_reg || !state) {
        return -1;
    }
    event_status_reg_t event_status;
    int32_t ret = ctx->read_reg(ctx->handle, EVENT_STATUS_REG, (uint8_t *)&event_status, 4);
    if (ret < 0) {
        return ret;
    } else {
        *state = event_status.unexpected_volt_on_vbus;
        return ret;
    }
}

int32_t cypd3177_check_is_vbus_volt_outside_expected_range(ctx_t *ctx, event_state_e *state) {
    if (!ctx || !ctx->write_reg || !ctx->read_reg || !state) {
        return -1;
    }
    event_status_reg_t event_status;
    int32_t ret = ctx->read_reg(ctx->handle, EVENT_STATUS_REG, (uint8_t *)&event_status, 4);
    if (ret < 0) {
        return ret;
    } else {
        *state = event_status.vbus_volt_outside_expected_range;
        return ret;
    }
}

int32_t cypd3177_read_gpio_level(ctx_t *ctx, uint8_t *gpio_level) {
    if (!ctx || !ctx->write_reg || !ctx->read_reg || !gpio_level) {
        return -1;
    }
    uint8_t gpio_level_reg;
    int32_t ret = ctx->read_reg(ctx->handle, READ_GPIO_LEVEL_REG, (uint8_t *)&gpio_level_reg, 1);
    if (ret < 0) {
        return ret;
    } else {
        *gpio_level = gpio_level_reg;
        return ret;
    }
}

int32_t cypd3177_sample_gpio(ctx_t *ctx, uint8_t *volt_level) {
    if (!ctx || !ctx->write_reg || !ctx->read_reg || !volt_level) {
        return -1;
    }
    uint8_t sample_gpio_reg;
    int32_t ret = ctx->read_reg(ctx->handle, SAMPLE_GPIO_REG, (uint8_t *)&sample_gpio_reg, 1);
    if (ret < 0) {
        return ret;
    } else {
        *volt_level = sample_gpio_reg;
        return ret;
    }
}

