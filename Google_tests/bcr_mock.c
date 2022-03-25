//
// Created by Administrator on 3/25/2022.
//

#include "bcr_mock.h"
#include <string.h>


static uint8_t* last_write_data;
static uint16_t last_write_reg;

void bcr_mock_create(uint8_t *data) {
    last_write_data = data;
}

int32_t platform_write(void *handle, uint16_t reg, const uint8_t *bufp, uint16_t len)
{
    if (bufp == NULL || len == 0) {
        return -1;
    }
    memcpy(last_write_data, bufp, len);
    last_write_reg = reg;
    return 0;
}
int32_t platform_read(void *handle, uint16_t reg, uint8_t *bufp, uint16_t len) {
    if (bufp == NULL || len == 0) {
        return -1;
    }
    memcpy(bufp, last_write_data, len);
    return 0;
}

uint16_t bcr_spy_last_register(void) {
    return last_write_reg;
}
