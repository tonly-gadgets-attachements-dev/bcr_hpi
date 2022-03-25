//
// Created by Administrator on 3/25/2022.
//

#include "bcr_mock.h"

int32_t platform_write(void *handle, uint16_t reg, const uint8_t *bufp, uint16_t len)
{
    if (bufp == NULL || len == 0) {
        return -1;
    }
    return 0;
}
int32_t platform_read(void *handle, uint16_t reg, uint8_t *bufp, uint16_t len) {
    if (bufp == NULL || len == 0) {
        return -1;
    }
    return 0;
}