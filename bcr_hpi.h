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
typedef struct
{
    uint8_t bit0 : 1;
    uint8_t bit1 : 1;
    uint8_t bit2 : 1;
    uint8_t bit3 : 1;
    uint8_t bit4 : 1;
    uint8_t bit5 : 1;
    uint8_t bit6 : 1;
    uint8_t bit7 : 1;
} bitwise_t;

#define PROPERTY_DISABLE (0U)
#define PROPERTY_ENABLE (1U)

typedef int32_t (*write_ptr)(void *, uint16_t, const uint8_t *, uint16_t);
typedef int32_t (*read_ptr)(void *, uint16_t, uint8_t *, uint16_t);

typedef struct
{
    write_ptr write_reg;
    read_ptr read_reg;
    void *handle;
} ctx_t;

/* Exported constants --------------------------------------------------------*/

/* Exported macros ------------------------------------------------------------*/
/**
 * @brief CYPD3177 I2C chip address
 *
 */
#define CYPD3177_I2C_ADDR_8bit (0b01100000)
#define CYPD3177_I2C_ADDR_7bit (CYPD3177_I2C_ADDR_8bit >> 1)

/* Private macros ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/**
 * @brief DEVICE_MODE register
 *
 */
#define DEVICE_MODE_REG (0x0000U)
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
#define SILICON_ID_REG (0x0002U)
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
#define INTERRUPT_REG (0x0006U)
/**
 * @brief register structure of @INTERRUPT_REG
 *
 */
typedef struct
{
    uint8_t device_interrupt : 1;
    uint8_t pd_port_interrupt : 1;
    uint8_t reserved : 6;
} interrupt_reg_t;

typedef enum
{
    no_int = 0,
    new_int = 1
} dev_or_pd_int_e;
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
#define PD_STATUS_REG (0x1008U)
/**
 * @brief register structure of @PD_STATUS_REG
 *
 */
typedef struct
{
    uint8_t defaul_cfg : 6;
    uint8_t current_port_data_role : 1;
    uint8_t reserved_a : 1;
    uint8_t current_port_power_role : 1;
    uint8_t reserved_b : 1;
    uint8_t contract_state : 1;
    uint8_t reserved_c : 3;
    uint8_t rp_state : 1;
    uint8_t policy_engine_state : 1;
    uint8_t pd_spec_ver : 2;
    uint8_t partner_pd_spec_ver : 1;
    uint8_t partner_unchunked_msg_spt_status : 1;
    uint16_t reserved_d : 12;
} pd_status_reg_t;

typedef enum
{
    ufp = 0,
    dfp = 1
} current_port_data_role_e;

typedef enum
{
    not_exist = 0,
    exist = 1
} contract_state_e;

typedef enum
{
    sink_tx_ok = 0,
    sink_tx_ng = 1
} rp_state_e;

typedef enum
{
    not_ready = 0,
    ready = 1
} policy_engine_state_e;

typedef enum
{
    pd_2_0 = 0,
    pd_3_0 = 1
} pd_spec_ver_e;

typedef enum
{
    nonsupport = 0,
    support = 1
} partner_unchunked_msg_spt_status_e;
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
int32_t cypd3177_get_partner_unchunked_msg_spt_status(ctx_t *ctx, partner_unchunked_msg_spt_status_e *msg_spt_state);

/**
 * @brief  TYPE_C_STATUS register
 *
 */
#define TYPE_C_STATUS_REG (0x100CU)
/**
 * @brief register structure of @TYPE_C_STATUS_REG
 *
 */
typedef struct
{
    uint8_t partner_conn_status : 1;
    uint8_t cc_polarity : 1;
    uint8_t attached_dev_type : 3;
    uint8_t reserved : 1;
    uint8_t type_c_cur_lvl : 2;
} type_c_status_reg_t;

typedef enum
{
    not_connected = 0,
    connected = 1
} partner_conn_status_e;

typedef enum
{
    cc1 = 0,
    cc2 = 1
} cc_polarity_e;

typedef enum
{
    nothing_attaced = 0,
    source_attached = 2,
    debug_accessory_attached = 3
} attached_dev_type_e;

typedef enum
{
    cur900 = 0,
    cur1500 = 1,
    cur3000 = 2
} type_c_cur_lvl_e;
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
int32_t cypd3177_get_type_c_cur_lvl(ctx_t *ctx, type_c_cur_lvl_e *cur_lvl);

/**
 * @brief  BUS_VOLTAGE register
 *
 */
#define BUS_VOLTAGE_REG (0x100DU)
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
#define CURRENT_PDO_REG (0x1010U)
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
#define CURRENT_RDO_REG (0x1014U)
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
#define SWAP_RESPONSE_REG (0x1028U)
/**
 * @brief register structure of @SWAP_RESPONSE_REG
 *
 */
typedef struct
{
    uint8_t dr_swap_response : 2;
    uint8_t reserved_a : 2;
    uint8_t vconn_swap_response : 2;
    uint8_t reserved_b : 2;
} swap_response_reg_t;

typedef enum
{
    accept_swap = 0,
    reject_swap = 1,
    send_wait_to_swap = 2,
    not_surport_swap = 3
} response_type_e;
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
#define EVENT_STATUS_REG (0x1044U)
/**
 * @brief register structure of @EVENT_STATUS_REG
 *
 */
typedef struct
{
    uint8_t type_c_dev_attached : 1;
    uint8_t type_c_dev_disconnected : 1;
    uint8_t pd_contract_nego_completed : 1;
    uint8_t power_role_swap_completed : 1;

    uint8_t data_role_swap_completed : 1;
    uint8_t vconn_swap_completed : 1;
    uint8_t hard_reset_received : 1;
    uint8_t hard_reset_sent : 1;

    uint8_t soft_reset_sent : 1;
    uint8_t cable_reset_sent : 1;
    uint8_t type_c_err_recovery_initiated : 1;
    uint8_t bcr_entered_source_disabled_state : 1;

    uint32_t reserved_a : 17;
    uint8_t unexpected_volt_on_vbus : 1;
    uint8_t vbus_volt_outside_expected_range : 1;
    uint8_t reserved_b : 1;
} event_status_reg_t;

typedef enum
{
    event_false = 0,
    event_true = 1
} event_state_e;
/**
 * @brief  Type-C Device Attached
 *
 * @param ctx communication interface
 * @param dr_swap_resp  Type-C Device Attached : Type-C Device Attached
 *
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_check_is_type_c_dev_attached(ctx_t *ctx, event_state_e *state);

/**
 * @brief  Type-C Device Disconnected
 *
 * @param ctx communication interface
 * @param dr_swap_resp  Type-C Device Attached : Type-C Device Disconnected
 *
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_check_is_type_c_dev_disconnected(ctx_t *ctx, event_state_e *state);

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
int32_t cypd3177_check_is_type_c_err_recovery_initiated(ctx_t *ctx, event_state_e *state);

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
#define READ_GPIO_LEVEL_REG (0x0082U)
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
#define SAMPLE_GPIO_REG (0x0083U)
/**
 * @brief register structure of @SAMPLE_GPIO_REG
 *
 */

/**
 * @brief   8-bit voltage level referenced to VDD, typically at 3.3V.
 *          So, 0V reads as 0x00 and VDD (or higher) reads as 0xFF.
 *
 * @param ctx communication interface
 * @param volt_level  Voltage Level
 *
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_sample_gpio(ctx_t *ctx, uint8_t *volt_level);

/**
 * @brief  RESET register
 * This register is used to either reset the device or the I2C block.
 * When the I2C block is reset, the I2C module used for the HPI is reconfigured. All outstanding commands and responses are flushed.
 * When the device is reset, BCR undergoes a full chip reset causing the Power Delivery contract to be renegotiated and the sink FET switch to be opened.
 * This will result in the system losing power if no alternative power source(such as a battery) is available.
 * Responses in DEV_RESPONSE after writing to this register:
 * 1. SUCCESS (0x02): When the I2C block has been reset successfully
 * 2. RESET_COMPLETE (0x80): When the device has been reset successfullyResponses in DEV_RESPONSE after writing to this register:
 */
#define RESET_REG (0x0008U)
/**
 * @brief register structure of @RESET_REG
 *
 */
typedef enum
{
    I2C_RESET = 0,
    DEV_RESET = 1
} reset_type_e;
/**
 * @brief This register is used to either reset the device or the I2C block.
 *
 * @param ctx communication interface
 * @param reset_type  Reset Type
 *
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_execute_reset(ctx_t *ctx, reset_type_e *reset_type);

/**
 * @brief  EVENT_MASK register
 * This register will enable the set of events that BCR will notify the system controller about.
 * Whenever BCR detects an event (or PD message) for which a mask bit is set, it asserts the INTR pin and sets the “Port Interrupt” bit in INTERRUPT register.
 * The actual event code will be available in the PD_RESPONSE register and any associated data will be available in the Data Memory.
 * Upon device reset, all mask bits are set to 0.
 */
#define EVENT_MASK_REG (0x1024U)
/**
 * @brief register structure of @EVENT_MASK_REG
 * @response Responses in DEV_RESPONSE after writing to this register:
 * 1. SUCCESS (0x02): When the I2C block has been reset successfully
 */
typedef struct
{
    uint8_t reserved_a : 2;
    uint8_t over_volt_detected : 1;
    uint8_t type_c_dev_attached : 1;
    uint8_t type_c_dev_disconnected : 1;

    uint8_t pd_contract_nego_completed : 1;
    uint8_t pd_ctrl_msg_received : 1;
    uint8_t vdm_received : 1;
    uint8_t src_capa_msg_received : 1;

    uint8_t sink_capa_msg_received : 1;
    uint8_t reserved_b : 1;
    uint8_t err_and_timeout : 1;
    uint8_t reserved_c : 1;

    uint8_t rp_value_changed : 1;
    uint8_t reserved_d : 3;
    uint8_t pd_3_0_ex_data_msg_received : 1;
    uint16_t reserved_e : 14;
} event_mask_reg_t;

typedef enum
{
    NOTIFY_DISENABLE = 0,
    NOTIFY_ENABLE = 1
} evt_notify_e;
/**
 * @brief  Over Voltage Detected Event
 *
 * @param ctx communication interface
 * @param noti  mask bit, 0: disable, 1: enable
 *
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_set_over_volt_detected_mask(ctx_t *ctx, evt_notify_e *noti);

/**
 * @brief  Type-C Device Attached Event
 *
 * @param ctx communication interface
 * @param noti  mask bit, 0: disable, 1: enable
 *
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_set_type_c_dev_attached_mask(ctx_t *ctx, evt_notify_e *noti);

/**
 * @brief  Type-C Device Disconnected Event
 *
 * @param ctx communication interface
 * @param noti  mask bit, 0: disable, 1: enable
 *
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_set_type_c_dev_disconnected_mask(ctx_t *ctx, evt_notify_e *noti);

/**
 * @brief  PD Contract Negotiation Completed Event
 *
 * @param ctx communication interface
 * @param noti  mask bit, 0: disable, 1: enable
 *
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_set_pd_contract_nego_completed_mask(ctx_t *ctx, evt_notify_e *noti);

/**
 * @brief  PD Control Message Received Event
 *
 * @param ctx communication interface
 * @param noti  mask bit, 0: disable, 1: enable
 *
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_set_pd_ctrl_msg_received_mask(ctx_t *ctx, evt_notify_e *noti);

/**
 * @brief  VDM Message Received Event
 *
 * @param ctx communication interface
 * @param noti  mask bit, 0: disable, 1: enable
 *
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_set_vdm_received_mask(ctx_t *ctx, evt_notify_e *noti);

/**
 * @brief  SRC Capability Message Received Event
 *
 * @param ctx communication interface
 * @param noti  mask bit, 0: disable, 1: enable
 *
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_set_src_capa_msg_received_mask(ctx_t *ctx, evt_notify_e *noti);

/**
 * @brief  Sink Capability Message Received Event
 *
 * @param ctx communication interface
 * @param noti  mask bit, 0: disable, 1: enable
 *
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_set_sink_capa_msg_received_mask(ctx_t *ctx, evt_notify_e *noti);

/**
 * @brief  RP Value Changed Event
 *
 * @param ctx communication interface
 * @param noti  mask bit, 0: disable, 1: enable
 *
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_set_rp_value_changed_mask(ctx_t *ctx, evt_notify_e *noti);

/**
 * @brief  Error and Timeout Event
 *
 * @param ctx communication interface
 * @param noti  mask bit, 0: disable, 1: enable
 *
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_set_err_and_timeout_mask(ctx_t *ctx, evt_notify_e *noti);

/**
 * @brief  PD 3.0 Extended Data Message Received Event
 *
 * @param ctx communication interface
 * @param noti  mask bit, 0: disable, 1: enable
 *
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_set_pd_3_0_ex_data_msg_received_mask(ctx_t *ctx, evt_notify_e *noti);

/**
 * @brief  DM_CONTROL register
 * The system controller can use this register to send various Power Delivery Data Messages to the Port Partner(SOP) or Type-C cable marker (SOP’ or SOP’’) devices.
 * This register is most typically used to send Vendor Defined Messages (VDM) to the port partner to perform design-specific operations.
 * To send any message, the system controller must follow these steps
 * 1. Update the Data Memory with the complete PD Data message (excluding the Message Header, which will be prepended by BCR).
 *    The message should be written in 32-bit chunks in little endian order.
 *    When sending VDMs, the Data Memory must also contain the VDM header along with the rest of the actual message.
 * 2. Write to the DM_CONTROL register with the Recipient Type (SOP=Port Partner, SOP*=Cable) and the size of the Data Message in bytes
 * 3. BCR will attempt to send the message. If the message was sent properly or if any errors are seen,
 *    it will notify the system controller and the response code will be placed in PD_RESPONSE register.
 * 4. If the port partner sends any response to the message sent by BCR, then BCR will notify the systemcontroller separately.
 *    To listen for such partner messages, write to the corresponding bit in the EVENT_MASK register or poll the EVENT_STATUS register.
 *
 * Responses in PD_RESPONSE after writing to this register:
 * 1. SUCCESS (0x02): If the Data Message was transmitted successfully (i.e GoodCRC was received from the recipient device)
 * 2. TRANSACTION_FAILED (0x0C): If the transmission failed i.e GoodCRC was not received
 * 3. INVALID_COMMAND (0x09): If any reserved bits are set
 * 4. PD_COMMAND_FAILED (0x0D): If the Type-C port is not connected to a partner, or if a PD contract does not exist, or if the BCR device is not ready to send the message.
 *    Check the “PE_Ready” and “Sink Tx OK” bits of PD_STATUS register to know if BCR is ready to send a message.
 */
#define DM_CONTROL_REG (0x1000U)
/**
 * @brief register structure of @DM_CONTROL_REG
 *
 */
typedef struct
{
    uint8_t packet_recipient_type : 2;
    uint8_t pd_3_0_data_msg : 1;
    uint8_t extented_data_msg : 1;
    uint8_t disable_send_res_timer : 1;

    uint8_t reserved : 1;
    uint8_t message_len_bits_9_8 : 2;
    uint8_t message_len_bits_7_0 : 8;
} dm_ctrl_reg_t;

/**
 * @brief  PD 3.0 Extended Data Message Received Event
 *
 * @param ctx communication interface
 * @param noti  mask bit, 0: disable, 1: enable
 *
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_set_dm_ctrl(ctx_t *ctx, dm_ctrl_reg_t *dm_ctrl);

/**
 * @brief  SELECT_SINK_PDO register
 * The system controller can use this register to send various Power Delivery Data Messages to the Port Partner(SOP) or Type-C cable marker (SOP’ or SOP’’) devices.
 * This register is most typically used to send Vendor Defined Messages (VDM) to the port partner to perform design-specific operations.
 * To send any message, the system controller must follow these steps
 * 1. Update the Data Memory with the complete PD Data message (excluding the Message Header, which will be prepended by BCR).
 *    The message should be written in 32-bit chunks in little endian order.
 *    When sending VDMs, the Data Memory must also contain the VDM header along with the rest of the actual message.
 * 2. Write to the DM_CONTROL register with the Recipient Type (SOP=Port Partner, SOP*=Cable) and the size of the Data Message in bytes
 * 3. BCR will attempt to send the message. If the message was sent properly or if any errors are seen,
 *    it will notify the system controller and the response code will be placed in PD_RESPONSE register.
 * 4. If the port partner sends any response to the message sent by BCR, then BCR will notify the systemcontroller separately.
 *    To listen for such partner messages, write to the corresponding bit in the EVENT_MASK register or poll the EVENT_STATUS register.
 *
 * Responses in PD_RESPONSE after writing to this register:
 * 1. SUCCESS (0x02): If the Data Message was transmitted successfully (i.e GoodCRC was received from the recipient device)
 * 2. TRANSACTION_FAILED (0x0C): If the transmission failed i.e GoodCRC was not received
 * 3. INVALID_COMMAND (0x09): If any reserved bits are set
 * 4. PD_COMMAND_FAILED (0x0D): If the Type-C port is not connected to a partner, or if a PD contract does not exist, or if the BCR device is not ready to send the message.
 *    Check the “PE_Ready” and “Sink Tx OK” bits of PD_STATUS register to know if BCR is ready to send a message.
 */
#define SELECT_SINK_PDO_REG (0x1000U)
/**
 * @brief register structure of @SELECT_SINK_PDO_REG
 *
 */
typedef struct
{
    uint8_t enable_pdo_1 : 1;
    uint8_t enable_pdo_2 : 1;
    uint8_t enable_pdo_3 : 1;
    uint8_t enable_pdo_4 : 1;

    uint8_t enable_pdo_5 : 1;
    uint8_t enable_pdo_6 : 1;
    uint8_t enable_pdo_7 : 1;
    uint8_t set_unconstrainrd_power_in_pdo_1 : 1;
} select_sink_pdo_reg_t;

/**
 * @brief  PD 3.0 Extended Data Message Received Event
 *
 * @param ctx communication interface
 * @param noti  mask bit, 0: disable, 1: enable
 *
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_select_sink_pdo(ctx_t *ctx, select_sink_pdo_reg_t *sink_pdo);

/**
 * @brief  PD_CONTROL(Send PD Control Message) register
 * This register is used to send Power Delivery Control messages to the port partner.
 * The port partner may respond back to a PD Control message sent using this register.
 * To look for these responses, poll the EVENT_STATUS register or enable the “PD Control Message Received” event in EVENT_MASK and wait for an interrupt from BCR.
 *
 * Responses in PD_RESPONSE after writing to this register:
 * 1. SUCCESS (0x02): If the PD Control message was sent successfully i.e GoodCRC was received from the bport partner
 * 2. TRANSACTION_FAILED (0x0C): If the transmission failed i.e GoodCRC was not received
 * 3. INVALID_COMMAND (0x09): If the command is any reserved value
 * 4. PD_COMMAND_FAILED (0x0D): If the Type-C port is not connected to a partner, or if a PD contract does not exist, or if the BCR device is not ready to send the message.
 *    Check the “PE_Ready” and “Sink Tx OK” bits of PD_STATUS register to know if BCR is ready to send a message.
 */
#define PD_CONTROL_REG (0x1006U)
/**
 * @brief register structure of @PD_CONTROL_REG
 *
 */
typedef struct
{
    uint8_t reserved_a : 5;
    uint8_t send_dr_swap_msg : 1;
    uint8_t reserved_b : 3;
    uint8_t send_vconn_swap_msg : 1;
    uint8_t send_get_source_cap_msg : 1;
    uint8_t reserved_c : 2;
    uint8_t send_hard_reset_msg : 1;
    uint8_t send_soft_reset_msg : 1;
    uint8_t reserved_d : 7;
    uint8_t send_get_source_cap_extd_msg : 1;
    uint8_t send_get_status_msg : 1;
    uint8_t send_get_not_supported_msg : 1;
    uint8_t reserved_e : 7;
} pd_ctrl_reg_t;

/**
 * @brief  Send DR_Swap message
 * BCR will attempt to send DR_Swap message and exchange data roles
 */
uint32_t cypd3177_send_dr_swap(ctx_t *ctx);

/**
 * @brief  Send VCONN_Swap message
 * BCR will attempt to send VCONN_Swap message and exchange VCONN source direction
 */
uint32_t cypd3177_send_vconn_swap(ctx_t *ctx);

/**
 * @brief  Send Get_Source_Cap message
 * BCR will attempt to retrieve the Port Partner’s Source Capabilities.
 * Note: This will cause PD contract to be renegotiated resulting in a power loss to the system
 */
uint32_t cypd3177_send_get_source_cap(ctx_t *ctx);

/**
 * @brief  Send Hard_Reset message
 * Note: This will cause PD contract to be renegotiated resulting in a power loss to the system
 */
uint32_t cypd3177_send_hard_reset(ctx_t *ctx);

/**
 * @brief  Send Soft_Reset message
 * Note: This may cause PD contract to be renegotiated resulting in a power loss to the system
 */
uint32_t cypd3177_send_soft_reset(ctx_t *ctx);

/**
 * @brief  Send Get_Source_Cap_Extd message
 *
 */
uint32_t cypd3177_send_get_source_cap_extd(ctx_t *ctx);

/**
 * @brief  Send Get_Status message
 *
 */
uint32_t cypd3177_send_get_status(ctx_t *ctx);

/**
 * @brief  Send Get_Not_Supported message
 *
 */
uint32_t cypd3177_send_get_not_supported(ctx_t *ctx);

/**
 * @brief  REQUEST register
 * This register is used to send a custom Request Data Object (RDO) to the port partner.
 * A write to this register will take effect only if the Sink PDO mask (in SELECT_SINK_PDO) is non-zero.
 * This requirement is made so that the system controller can fully determine the state of the PD contract.
 *
 * When the system controller writes to this register, BCR sends the request as-is to the port partner.
 * BCR will not validate the contents of the packet.
 * If the packet is malformed or if some bits are not set correctly, then the port partner may issue Soft Resets or Hard Resets to BCR causing the system to lose power.
 *
 * The port partner may respond back to a PD Control message sent using this register.
 * To look for these responses, poll the EVENT_STATUS register or enable the “PD Control Message Received” event in EVENT_MASK and wait for an interrupt from BCR.
 *
 * Responses in PD_RESPONSE after writing to this register:
 * 1. SUCCESS (0x02): Request message was queued to be sent to the port partner.
 *    A SUCCESS does not guarantee that GoodCRC was received, nor does it guarantee successful PD Contract renegotiation.
 *    Look for events in the EVENT_STATUS register or listen to events using EVENT_MASK for more details.
 * 2. COMMAND_FAILED (0x06): If the Request message could not be sent. Try again later.
 */
#define REQUEST_REG (0x1050U)
/**
 * @brief register structure of @REQUEST_REG
 *
 */

/**
 * @brief  Send 32-bit Request Data Object
 * Contents of the RDO to be sent out, in little endian order
 *
 */
uint32_t cypd3177_send_request(ctx_t *ctx, uint32_t rdo);

/**
 * @brief  SET_GPIO_MODE register
 * This register is used to change the mode of the GPIO_1 pin in BCR.
 *
 * Responses in DEV_RESPONSE after writing to this register:
 * 1. SUCCESS (0x02): The GPIO drive mode was changed successfully
 */
#define SET_GPIO_MODE_REG (0x0080U)
/**
 * @brief register structure of @SET_GPIO_MODE_REG
 *
 */
typedef enum
{
    ANALOG_INPUT = 0,                 // for ADC usage
    HIGH_IMPEDANCE_DIGITAL_INPUT = 1, // external driver on the pin
    RESISTIVE_PULL_UP = 2,            // Strong Low, Weak High
    RESISTIVE_PULL_DOWN = 3,          // Strong High, Weak Low
    OPEN_DRAIN_LOW = 4,               // Open Drain
    OPEN_DRAIN_HIGH = 5,              // Open Drain
    STRONG_DRIVE = 6,                 // Strong Low, Strong High
    RESISTIVE_DRIVE = 7               // Weak High, Weak Low
} gpio_drive_mode_e;

/**
 * @brief  Set GPIO_1 Drive Mode
 * Contents of the RDO to be sent out, in little endian order
 *
 */
uint32_t cypd3177_set_gpio_drive_mode(ctx_t *ctx, gpio_drive_mode_e drive_mode);

/**
 * @brief  SET_GPIO_LEVEL register
 * This register is used to change the drive level of the GPIO_1 pin in BCR.
 *
 * Responses in DEV_RESPONSE after writing to this register:
 * 1. SUCCESS (0x02): The GPIO drive level was changed successfully
 * 2. INVALID_ARGUMENT (0x09): The GPIO drive mode (set by SET_GPIO_MODE) was “Analog”.
 *    Change the mode to one of the digital drives before changing its level.
 */
#define SET_GPIO_LEVEL_REG (0x0081U)
/**
 * @brief register structure of @SET_GPIO_LEVEL_REG
 *
 */
typedef enum
{
    DRIVE_LOW = 0,
    DRIVE_HIGH = 1
} gpio_lvl_e;

/**
 * @brief  Set GPIO_1 Drive Mode
 * Contents of the RDO to be sent out, in little endian order
 *
 */
uint32_t cypd3177_set_gpio_lvl(ctx_t *ctx, gpio_lvl_e lvl);

/**
 * @brief  RESPONSE Codes
 * BCR can send 2 types of responses
 * 1. Responses to Command Registers
 * This can be of two types: responses to device-specific commands and responses to port-specific commands
 * 2. Asynchronous events
 * This can also be of two types: events generated by device state change or events generated when PD port state changes
 */
typedef enum
{
    NO_RESP = 0x00,
    SUCCESS = 0x02,
    INVALID_CMD = 0x05,
    INVALID_ARGUMENT = 0x09,
    NOT_SUPPORTED = 0x0A,
    TRANS_FAILED = 0x0C,
    PD_CMD_FAILED = 0x0D,
    PORT_BUSY = 0x12
} resp_to_cmd_e;

typedef enum
{
    RESET_COMPLETE = 0x80,
    MSG_QUEUE_OVERFLOW = 0x81,
    VBUS_OVER_VOLTAGE_DETECTED = 0x83
} asyn_dev_evt_e;

typedef enum
{
    TYPE_C_CONNECTED = 0x84,
    TYPE_C_DISCONNECTED = 0x85,
    PD_CONTRACT_NEGO_COMPLETE = 0x86,
    SWAP_COMPLETE = 0x87,
    PS_RDY = 0x8A,
    GOTOMIN = 0x8B,
    ACCEPT = 0x8C,
    REJECT = 0x8D,
    WAIT = 0x8E,
    HARD_RESET = 0x8F,
    VDM_RECEIVED = 0x90,
    SOURCE_CAP = 0x91,
    SINK_CAP = 0x92,
    HARD_RESET_SENT = 0x9A,
    SOFT_RESET_SENT = 0x9B,
    SOURCE_DISABLED = 0x9D,
    NO_VDM_RESP = 0x9F,
    TYPE_C_ERR_RECOVERY = 0xA1,
    BAT_STATUS_RECEIVED = 0xA2,
    ALERT_RECEIVED = 0xA3,
    NOT_SUPPORTED_RECEIVED = 0xA4,
    RP_CHANGE_DETECTED = 0xAA,
    EXT_DATA_RECEIVED = 0xAC,
    CC_OVP = 0xBA
} asyn_port_evt_e;

/**
 * @brief  DEV_RESPONSE register
 * The Device Response (DEV_RESPONSE) register is used to store responses to commands sent on certain Command Registers.
 * In addition, this register will also hold device events such as reset completion.
 */
#define DEV_RESPONSE_REG (0x007EU)
/**
 * @brief register structure of @DEV_RESPONSE_REG
 *
 */
typedef struct
{
    uint8_t resp_code : 7;
    uint8_t resp_type : 1;
    uint8_t resp_len : 8;
} dev_resp_t;
typedef enum
{
    CMD_WRITE_RESP = 0,
    ASYN_EVT_RESP = 1
} resp_type_e;

/**
 * @brief  Get DEV_RESPONSE
 *
 */
uint32_t cypd3177_get_dev_resp(ctx_t *ctx, dev_resp_t *dev_resp);

/**
 * @brief  PD_RESPONSE register
 * The Device Response (DEV_RESPONSE) register is used to store responses to commands sent on certain Command Registers.
 * In addition, this register will also hold device events such as reset completion.
 */
#define PD_RESPONSE_REG (0x1400U)
/**
 * @brief register structure of @PD_RESPONSE_REG
 *
 */
typedef struct
{
    uint8_t resp_code : 7;
    uint8_t resp_type : 1;
    uint8_t resp_len1 : 8;
    uint16_t resp_len2 : 16;
} pd_resp_t;

/**
 * @brief  Get DEV_RESPONSE
 *
 */
uint32_t cypd3177_get_pd_resp(ctx_t *ctx, pd_resp_t *pd_resp);

/**
 * @brief  DATA_MEMORY_REGIONS
 * The Data Memory is split into two regions: Read Data Memory and Write Data Memory.
 *
 * Read Data Memory : 0x1404 to 0x150B
 * The 264-byte Read Data Memory is placed adjacent to the PD_RESPONSE register so that it can be read in one single I2C read.
 * This region will contain the PD Message data, contract information and other information as listed in the Response Codes section.
 * Write Data Memory : 0x1800 to 0x19FF
 * The 512-byte Write Data Memory is used when writing to Command Registers to send additional data for the command.
 *
 * Any write or read from a Data Memory region will not trigger an INTR assertion. Reads or writes beyond the expected address range will be NAKed.
 */
#define READ_DATA_MEMORY_REG (0x1404U)
#define WRITE_DATA_MEMORY_REG (0x1800U)
/**
 * @brief register structure of @DATA_MEMORY_REGIONS_REG
 *
 */

/**
 * @brief  Read Data Memory
 *
 */
uint32_t cypd3177_read_data_memory(ctx_t *ctx, uint8_t *data, uint16_t len);

/**
 * @brief  Write Data Memory
 *
 */
uint32_t cypd3177_write_data_memory(ctx_t *ctx, uint8_t *data, uint16_t len);
/*! @} */
#endif //_BCR_HPI_H
