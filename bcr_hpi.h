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
int32_t cypd3177_get_test_interrupt(ctx_t *ctx, uint8_t *pd_int);

/*! @} */
#endif //_BCR_HPI_H
