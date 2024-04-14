#pragma once

#include "platform.h"

typedef struct flashPage_t {
    uint32_t x[FLASH_PAGE_SIZE / 4];
} flashPage_t;

/** Read from flash memory. */
void flashRead(uint32_t address, flashPage_t *data, uint8_t page_cnt);

/** Write to flash memory. */
void flashWrite(uint32_t address, flashPage_t *data, uint8_t page_cnt);