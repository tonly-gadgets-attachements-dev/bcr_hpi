//
// Created by Administrator on 3/25/2022.
//

#ifndef GOOGLE_TESTS_BCR_MOCK_H
#define GOOGLE_TESTS_BCR_MOCK_H
#include <stdint.h>
void bcr_mock_create(uint8_t *data);
int32_t platform_write(void *handle, uint16_t reg, const uint8_t *bufp, uint16_t len);
int32_t platform_read(void *handle, uint16_t reg, uint8_t *bufp, uint16_t len);
uint16_t bcr_spy_last_register(void);
#endif //GOOGLE_TESTS_BCR_MOCK_H
