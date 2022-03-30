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
/**
 * @brief get device interrupt
 *
 * @param ctx communication interface
 * @param device_int device interrupt
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_get_device_interrupt(ctx_t *ctx, uint8_t *device_int);

/**
 * @brief get pd interrupt
 *
 * @param ctx communication interface
 * @param pd_int pd interrupt
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_get_pd_interrupt(ctx_t *ctx, uint8_t *pd_int);

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
/**
 * @brief get the default PD configuration of BCR (UFP Data Role and Sink Power Role)
 *
 * @param ctx communication interface
 * @param pd_status PD_STATUS register : Default Config(UFP Data Role and Sink Power Role)
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_get_default_config(ctx_t *ctx, uint8_t *pd_status);

/**
 * @brief Current Port Data Role.
 *
 * @param ctx communication interface
 * @param pd_status PD_STATUS register : Current Port Data Role
 *                  0 = UFP
 *                  1 = DFP
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_get_cur_port_data_role(ctx_t *ctx, uint8_t *pd_status);

/**
 * @brief Current Port Power Role
 *
 * @param ctx communication interface
 * @param pd_status PD_STATUS register : Current Port Power Role
 *                  0 = Sink;BCR always functions as a sink and so this bit is never expected to be set to 1.
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_get_cur_port_power_role(ctx_t *ctx, uint8_t *pd_status);

/**
 * @brief Contract State
 *
 * @param ctx communication interface
 * @param pd_status PD_STATUS register : Contract State
 *                  0 = No contract exists with port partner
 *                  1 = Explicit PD contract exists with port partner
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_get_contract_state(ctx_t *ctx, uint8_t *pd_status);

/**
 * @brief Sink Tx Ready Status (Rp state)
 *
 * @param ctx communication interface
 * @param pd_status PD_STATUS register : Contract State
 *                  0 = Rp is in SinkTxOk (Sink can send messages to Source)
 *                  1 = Rp is in SinkTxNG (Sink shouldn’t send messages)
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_get_rp_state(ctx_t *ctx, uint8_t *pd_status);

/**
 * @brief Policy Engine State (see Chapter 8 of PD spec)
 *
 * @param ctx communication interface
 * @param pd_status PD_STATUS register : Policy Engine State (see Chapter 8 of PD spec)
 *                  0 = Port is not in PE_SNK_Ready state
 *                  1 = Port is in PE_SNK_Ready state
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_get_policy_engine_state(ctx_t *ctx, uint8_t *pd_status);

/**
 * @brief PD Spec revision supported by BCR
 *
 * @param ctx communication interface
 * @param pd_status PD_STATUS register : PD Spec revision supported by BCR
 *                  0 = PD 2.0
 *                  1 = PD 3.0
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_get_pd_spec_ver(ctx_t *ctx, uint8_t *pd_status);

/**
 * @brief Partner (Attached device) PD Spec revision
 *
 * @param ctx communication interface
 * @param pd_status PD_STATUS register : Partner (Attached device) PD Spec revision
 *                  0 = Partner is PD 2.0 device
 *                  1 = Partner is PD 3.0 device
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_get_partner_pd_spec_ver(ctx_t *ctx, uint8_t *pd_status);

/**
 * @brief Partner (Attached device) PD Spec revision
 *
 * @param ctx communication interface
 * @param pd_status PD_STATUS register : Partner (Attached device) PD Spec revision
 *                  0 = PPartner doesn’t support un-chunked messages
 *                  1 = PPartner supports un-chunked messages
 * @return int32_t inherited from user communication method
 */
int32_t cypd3177_get_partner_unchunked_msg_spt_status (ctx_t *ctx, uint8_t *pd_status);


/*! @} */
#endif //_BCR_HPI_H
