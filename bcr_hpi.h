//
// Created by Administrator on 3/25/2022.
//

#ifndef _BCR_HPI_H
#define _BCR_HPI_H
/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
/*! \addtogroup aw21024_interfaces
 *
 * @{
 */
/* Exported types ------------------------------------------------------------*/
typedef struct{
    uint8_t bit0       : 1;
    uint8_t bit1       : 1;
    uint8_t bit2       : 1;
    uint8_t bit3       : 1;
    uint8_t bit4       : 1;
    uint8_t bit5       : 1;
    uint8_t bit6       : 1;
    uint8_t bit7       : 1;
} bitwise_t;

#define PROPERTY_DISABLE                (0U)
#define PROPERTY_ENABLE                 (1U)

typedef int32_t (*write_ptr)(void *, uint16_t, const uint8_t *, uint16_t);
typedef int32_t (*read_ptr) (void *, uint16_t, uint8_t *, uint16_t);

typedef struct{
    write_ptr write_reg;
    read_ptr  read_reg;
    void      *handle;
}ctx_t;

/* Exported constants --------------------------------------------------------*/

/* Exported macros ------------------------------------------------------------*/
/**
 * @brief CYPD3177 I2C chip address
 *
*/
#define CYPD3177_I2C_ADDR_8bit           (0b01100000)
#define CYPD3177_I2C_ADDR_7bit           (CYPD3177_I2C_ADDR_8bit >> 1)

/* Private macros ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/**
 * @brief DEVICE_MODE register
 *
 */
#define DEVICE_MODE_REG                  (0x0000U)
/**
 * @brief get current device mode
 *
 * @param ctx communication interface
 * @param mode current mode, always as 0x92U
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_get_device_mode(ctx_t *ctx, uint8_t *mode);

/**
 * @brief  SILICON_ID register
 *
 */
#define SILICON_ID_REG                    (0x0002U)
/**
 * @brief get silicon id
 *
 * @param ctx communication interface
 * @param id silicon id, uint16_t, always as 0x11B0U
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_get_silicon_id(ctx_t *ctx, uint16_t *id);

/**
 * @brief  INTERRUPT register
 *
 */
#define INTERRUPT_REG                     (0x0006U)
/**
 * @brief register structure of @INTERRUPT_REG
 *
 */
typedef struct {
    uint8_t device_interrupt    :1;
    uint8_t pd_port_interrupt   :1;
    uint8_t reserved            :6;
}interrupt_reg_t;

typedef enum{
    no_int = 0,
    new_int = 1
}dev_or_pd_int_e;
/**
 * @brief get device interrupt
 *
 * @param ctx communication interface
 * @param device_int device interrupt
 *              0 = No device interrupt pending
 *              1 = New response available in DEV_RESPONSE register
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_get_device_interrupt(ctx_t *ctx, dev_or_pd_int_e *device_int);

/**
 * @brief get pd interrupt
 *
 * @param ctx communication interface
 * @param pd_int pd interrupt
 *              0 = No port interrupt pending
 *              1 = New response available in PD_RESPONSE register
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_get_pd_interrupt(ctx_t *ctx, dev_or_pd_int_e *pd_int);

/**
 * @brief  PD_STATUS register
 *
 */
#define PD_STATUS_REG                     (0x1008U)
/**
 * @brief register structure of @PD_STATUS_REG
 *
 */
typedef struct {
    uint8_t defaul_cfg                          :6;
    uint8_t current_port_data_role              :1;
    uint8_t reserved_a                          :1;
    uint8_t current_port_power_role             :1;
    uint8_t reserved_b                          :1;
    uint8_t contract_state                      :1;
    uint8_t reserved_c                          :3;
    uint8_t rp_state                :1;
    uint8_t policy_engine_state                 :1;
    uint8_t pd_spec_ver                         :2;
    uint8_t partner_pd_spec_ver                 :1;
    uint8_t partner_unchunked_msg_spt_status    :1;
    uint16_t reserved_d                         :12;
}pd_status_reg_t;

typedef enum{
    ufp = 0,
    dfp = 1
}current_port_data_role_e;

typedef enum{
    not_exist = 0,
    exist = 1
}contract_state_e;

typedef enum{
    sink_tx_ok = 0,
    sink_tx_ng = 1
}rp_state_e;

typedef enum{
    not_ready = 0,
    ready = 1
}policy_engine_state_e;

typedef enum{
    pd_2_0 = 0,
    pd_3_0 = 1
}pd_spec_ver_e;

typedef enum{
    nonsupport = 0,
    support = 1
}partner_unchunked_msg_spt_status_e;
/**
 * @brief get the default PD configuration of BCR (UFP Data Role and Sink Power Role)
 *
 * @param ctx communication interface
 * @param df_cfg PD_STATUS register : Default Config(UFP Data Role and Sink Power Role)
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_get_default_config(ctx_t *ctx, uint8_t *df_cfg);

/**
 * @brief Current Port Data Role.
 *
 * @param ctx communication interface
 * @param data_role PD_STATUS register : Current Port Data Role
 *                  0 = UFP
 *                  1 = DFP
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_get_cur_port_data_role(ctx_t *ctx, current_port_data_role_e *data_role);

/**
 * @brief Current Port Power Role
 *
 * @param ctx communication interface
 * @param pwr_role PD_STATUS register : Current Port Power Role
 *                  0 = Sink;BCR always functions as a sink and so this bit is never expected to be set to 1.
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_get_cur_port_power_role(ctx_t *ctx, uint8_t *pwr_role);

/**
 * @brief Contract State
 *
 * @param ctx communication interface
 * @param contract_state PD_STATUS register : Contract State
 *                  0 = No contract exists with port partner
 *                  1 = Explicit PD contract exists with port partner
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_get_contract_state(ctx_t *ctx, contract_state_e *contract_state);

/**
 * @brief Sink Tx Ready Status (Rp state)
 *
 * @param ctx communication interface
 * @param rp_state PD_STATUS register : Contract State
 *                  0 = Rp is in SinkTxOk (Sink can send messages to Source)
 *                  1 = Rp is in SinkTxNG (Sink shouldn’t send messages)
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_get_rp_state(ctx_t *ctx, rp_state_e *rp_state);

/**
 * @brief Policy Engine State (see Chapter 8 of PD spec)
 *
 * @param ctx communication interface
 * @param pe_state PD_STATUS register : Policy Engine State (see Chapter 8 of PD spec)
 *                  0 = Port is not in PE_SNK_Ready state
 *                  1 = Port is in PE_SNK_Ready state
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_get_policy_engine_state(ctx_t *ctx, policy_engine_state_e *pe_state);

/**
 * @brief PD Spec revision supported by BCR
 *
 * @param ctx communication interface
 * @param pd_ver PD_STATUS register : PD Spec revision supported by BCR
 *                  0 = PD 2.0
 *                  1 = PD 3.0
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_get_pd_spec_ver(ctx_t *ctx, pd_spec_ver_e *pd_ver);

/**
 * @brief Partner (Attached device) PD Spec revision
 *
 * @param ctx communication interface
 * @param pd_ver PD_STATUS register : Partner (Attached device) PD Spec revision
 *                  0 = Partner is PD 2.0 device
 *                  1 = Partner is PD 3.0 device
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_get_partner_pd_spec_ver(ctx_t *ctx, pd_spec_ver_e *pd_ver);

/**
 * @brief Partner (Attached device) PD Spec revision
 *
 * @param ctx communication interface
 * @param msg_spt_state PD_STATUS register : Partner (Attached device) PD Spec revision
 *                  0 = PPartner doesn’t support un-chunked messages
 *                  1 = PPartner supports un-chunked messages
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_get_partner_unchunked_msg_spt_status (ctx_t *ctx, partner_unchunked_msg_spt_status_e *msg_spt_state);


/**
 * @brief  TYPE_C_STATUS register
 *
 */
#define TYPE_C_STATUS_REG                     (0x100CU)
/**
 * @brief register structure of @TYPE_C_STATUS_REG
 *
 */
typedef struct {
    uint8_t partner_conn_status     :1;
    uint8_t cc_polarity             :1;
    uint8_t attached_dev_type       :3;
    uint8_t reserved                :1;
    uint8_t typec_cur_lvl           :2;
}typec_status_reg_t;

typedef enum{
    not_connected = 0,
    connected = 1
}partner_conn_status_e;

typedef enum{
    cc1 = 0,
    cc2 = 1
}cc_polarity_e;

typedef enum{
    nothing_attaced = 0,
    source_attached = 2,
    debug_accessory_attached = 3
}attached_dev_type_e;

typedef enum{
    cur900 = 0,
    cur1500 = 1,
    cur3000 = 2
}typec_cur_lvl_e;
/**
 * @brief Port Partner Connection Status
 *
 * @param ctx communication interface
 * @param conn_status TYPE_C_STATUS : Port Partner Connection Status
 *              0 = Port is not connected to partner
 *              1 = Port is connected to partner
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_get_partner_conn_status(ctx_t *ctx, partner_conn_status_e *conn_status);

/**
 * @brief CC Polarity
 *
 * @param ctx communication interface
 * @param cc_polarity TYPE_C_STATUS : CC Polarity
 *              0 = CC1
 *              1 = CC2
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_get_cc_polarity(ctx_t *ctx, cc_polarity_e *cc_polarity);

/**
 * @brief Attached device type
 *
 * @param ctx communication interface
 * @param dev_type TYPE_C_STATUS : Attached device type
 *              000 = Nothing attached
 *              010 = Source attached
 *              011 = Debug Accessory attached
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_get_attached_dev_type(ctx_t *ctx, attached_dev_type_e *dev_type);

/**
 * @brief Type-C Current Level (Rp of partner device)
 * This is the Rp value advertised by the attached port partner.
 * If the CC line voltage is invalid, then this field will indicate 00.
 *
 * @param ctx communication interface
 * @param cur_lvl TYPE_C_STATUS : Type-C Current Level
 *              00 = Default (900mA)
 *              01 = 1.5A
 *              10 = 3A
 *              11 = Reserved
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_get_typec_cur_lvl(ctx_t *ctx, typec_cur_lvl_e *cur_lvl);


/**
 * @brief  BUS_VOLTAGE register
 *
 */
#define BUS_VOLTAGE_REG                     (0x100DU)
/**
 * @brief register structure of @BUS_VOLTAGE_REG
 *
 */

/**
 * @brief Live VBUS voltage
 *
 * @param ctx communication interface
 * @param vol Voltage on the VBUS line
 *
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_get_vbus_vol(ctx_t *ctx, uint16_t *vol);


/**
 * @brief  CURRENT_PDO register
 *
 */
#define CURRENT_PDO_REG                 (0x1010U)
/**
 * @brief register structure of @CURRENT_PDO_REG
 *
 */

/**
 * @brief CURRENT_PDO
 *
 * @param ctx communication interface
 * @param pdo Active PDO.
 * This is the 32-bit Power Data Object (PDO) that was most recently received from the attached Source.
 *
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_get_cur_pdo(ctx_t *ctx, uint32_t *pdo);


/**
 * @brief  CURRENT_RDO register
 *
 */
#define CURRENT_RDO_REG                 (0x1014U)
/**
 * @brief register structure of @CURRENT_PDO_REG
 *
 */

/**
 * @brief CURRENT_RDO
 *
 * @param ctx communication interface
 * @param pdo Active RDO.
 * This is the 32-bit Request Data Object (PDO) that was most recently sent from BCR to the attached Source.
 *
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_get_cur_rdo(ctx_t *ctx, uint32_t *rdo);


/**
 * @brief  SWAP_RESPONSE register
 *
 */
#define SWAP_RESPONSE_REG                     (0x1028U)
/**
 * @brief register structure of @SWAP_RESPONSE_REG
 *
 */
typedef struct {
    uint8_t dr_swap_response    :2;
    uint8_t reserved_a          :2;
    uint8_t vconn_swap_response :2;
    uint8_t reserved_b          :2;
}swap_response_reg_t;

typedef enum{
    accept_swap = 0,
    reject_swap = 1,
    send_wait_to_swap = 2,
    not_surport_swap = 3
}response_type_e;
/**
 * @brief DR_Swap Response
 *
 * @param ctx communication interface
 * @param dr_swap_resp DR_Swap Response
 *              00 = Accept Swap
 *              01 = Reject Swap
 *              10 = Send Wait to the swap message
 *              11 = Swap is not supported (in PD 2.0 contracts, BCR will send “Reject”; in PD 3.0 contracts, BCR will send “Not_Supported”)
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_get_de_swap_response(ctx_t *ctx, response_type_e *dr_swap_resp);

/**
 * @brief VCONN_Swap Response
 *
 * @param ctx communication interface
 * @param vconn_swap_resp DR_Swap Response
 *              00 = Accept Swap
 *              01 = Reject Swap
 *              10 = Send Wait to the swap message
 *              11 = Swap is not supported (in PD 2.0 contracts, BCR will send “Reject”; in PD 3.0 contracts, BCR will send “Not_Supported”)
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_get_vconn_swap_response(ctx_t *ctx, response_type_e *vconn_swap_resp);


/**
 * @brief  EVENT_STATUS register
 *
 */
#define EVENT_STATUS_REG                     (0x1044U)
/**
 * @brief register structure of @EVENT_STATUS_REG
 *
 */
typedef struct {
    uint8_t typec_dev_attached                  :1;
    uint8_t typec_dev_disconnected              :1;
    uint8_t pd_contract_nego_completed          :1;
    uint8_t power_role_swap_completed           :1;

    uint8_t data_role_swap_completed            :1;
    uint8_t vconn_swap_completed                :1;
    uint8_t hard_reset_received                 :1;
    uint8_t hard_reset_sent                     :1;

    uint8_t soft_reset_sent                     :1;
    uint8_t cable_reset_sent                    :1;
    uint8_t typec_err_recovery_initiated        :1;
    uint8_t bcr_entered_source_disabled_state   :1;

    uint32_t reserved_a                         :17;
    uint8_t unexpected_volt_on_vbus             :1;
    uint8_t vbus_volt_outside_expected_range :1;
    uint8_t reserved_b                          :1;
}event_status_reg_t;

typedef enum{
    event_false = 0,
    event_true = 1
}event_state_e;
/**
 * @brief  Type-C Device Attached
 *
 * @param ctx communication interface
 * @param dr_swap_resp  Type-C Device Attached : Type-C Device Attached
 *
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_check_is_typec_dev_attached(ctx_t *ctx, event_state_e *state);

/**
 * @brief  Type-C Device Disconnected
 *
 * @param ctx communication interface
 * @param dr_swap_resp  Type-C Device Attached : Type-C Device Disconnected
 *
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_check_is_typec_dev_disconnected(ctx_t *ctx, event_state_e *state);

/**
 * @brief  PD Contract Negotiation Completed
 *
 * @param ctx communication interface
 * @param dr_swap_resp  PD Contract Negotiation Completed : PD Contract Negotiation Completed
 *
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_check_is_pd_contract_nego_completed(ctx_t *ctx, event_state_e *state);

/**
 * @brief  Power Role Swap Completed
 *
 * @param ctx communication interface
 * @param dr_swap_resp  Power Role Swap Completed : Power Role Swap Completed
 *
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_check_is_power_role_swap_completed(ctx_t *ctx, event_state_e *state);

/**
 * @brief  Data Role Swap Completed
 *
 * @param ctx communication interface
 * @param dr_swap_resp  Data Role Swap Completed : Data Role Swap Completed
 *
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_check_is_data_role_swap_completed(ctx_t *ctx, event_state_e *state);

/**
 * @brief  VCONN Swap Completed
 *
 * @param ctx communication interface
 * @param dr_swap_resp  VCONN Swap Completed : VCONN Swap Completed
 *
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_check_is_vconn_swap_completed(ctx_t *ctx, event_state_e *state);

/**
 * @brief  Hard Reset Received
 *
 * @param ctx communication interface
 * @param dr_swap_resp  Hard Reset Received : Hard Reset Received
 *
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_check_is_hard_reset_received(ctx_t *ctx, event_state_e *state);

/**
 * @brief  Hard Reset Sent
 *
 * @param ctx communication interface
 * @param dr_swap_resp  Hard Reset Sent : Hard Reset Sent
 *
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_check_is_hard_reset_sent(ctx_t *ctx, event_state_e *state);

/**
 * @brief  Soft Reset Sent
 *
 * @param ctx communication interface
 * @param dr_swap_resp  Soft Reset Sent : Soft Reset Sent
 *
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_check_is_soft_reset_sent(ctx_t *ctx, event_state_e *state);

/**
 * @brief  Cable Reset Sent
 *
 * @param ctx communication interface
 * @param dr_swap_resp  Cable Reset Sent : Cable Reset Sent
 *
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_check_is_cable_reset_sent(ctx_t *ctx, event_state_e *state);

/**
 * @brief  Type-C Error Recovery Initiated
 *
 * @param ctx communication interface
 * @param dr_swap_resp  Type-C Error Recovery Initiated : Type-C Error Recovery Initiated
 *
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_check_is_typec_err_recovery_initiated(ctx_t *ctx, event_state_e *state);

/**
 * @brief  BCR Entered Source Disabled State
 *
 * @param ctx communication interface
 * @param dr_swap_resp  BCR Entered Source Disabled State : BCR Entered Source Disabled State
 *
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_check_is_bcr_entered_src_disabled_state(ctx_t *ctx, event_state_e *state);

/**
 * @brief   Unexpected voltage on VBUS
 *
 * @param ctx communication interface
 * @param dr_swap_resp  BCR Entered Sink Disabled State :  Unexpected voltage on VBUS
 *
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_check_is_unexpected_volt_on_vbus(ctx_t *ctx, event_state_e *state);

/**
 * @brief   VBUS voltage is outside expected range
 *
 * @param ctx communication interface
 * @param dr_swap_resp  BCR Entered Sink Disabled State :  VBUS voltage is outside expected range
 *
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_check_is_vbus_volt_outside_expected_range(ctx_t *ctx, event_state_e *state);


/**
 * @brief  READ_GPIO_LEVEL register
 * This register is used to read the logic level of the GPIO_1 pin in BCR.
 * The mode of the GPIO should be set to one of the digital drive modes (Values 1~7 in SET_GPIO_MODE) before reading this register.
 * Else, this register will always contain 0x00.
 */
#define READ_GPIO_LEVEL_REG                     (0x0082U)
/**
 * @brief register structure of @READ_GPIO_LEVEL_REG
 *
 */
/*! @} */

/**
 * @brief   VBUS voltage is outside expected range
 *
 * @param ctx communication interface
 * @param gpio_level  GPIO level
 *
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_read_gpio_level(ctx_t *ctx, uint8_t *gpio_level);

/**
 * @brief  SAMPLE_GPIO register
 * This register is used to sample the voltage on the GPIO_1 pin in BCR.
 * The mode of the GPIO should be set to Analog mode (Value 0 in SET_GPIO_MODE) before reading this register.
 * Else, this register will always contain 0x00.
 */
#define SAMPLE_GPIO_REG                     (0x0083U)
/**
 * @brief register structure of @SAMPLE_GPIO_REG
 *
 */


/**
 * @brief   VBUS voltage is outside expected range
 *
 * @param ctx communication interface
 * @param volt_level  Voltage Level
 *
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_sample_gpio(ctx_t *ctx, uint8_t *volt_level);
/*! @} */
#endif //_BCR_HPI_H
