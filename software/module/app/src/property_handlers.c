#include "property_handlers.h"
#include "config.h"
#include "debug_io.h"
#include "flash.h"
#include "memory_map.h"

static openflap_ctx_t *openflap_ctx = NULL;

void firmware_property_set(uint8_t *buf)
{
    uint8_t app_index = (openflap_ctx->config.active_app_index + 1) % 2;
    uint32_t addr_base = APP_START_PTR + (app_index * APP_SIZE / 4);
    uint32_t addr_offset = ((uint32_t)buf[0] << 8 | buf[1]) * FLASH_PAGE_SIZE;
    uint32_t addr = addr_base + addr_offset;
    flashWrite(addr, (buf + 2), FLASH_PAGE_SIZE);
    if (addr_offset + FLASH_PAGE_SIZE == APP_SIZE) {
        openflap_ctx->config.active_app_index = app_index;
        openflap_ctx->store_config = true;
    }
}

void command_property_set(uint8_t *buf)
{
    // TODO
}

void columnEnd_property_get(uint8_t *buf)
{
    buf[0] = HAL_GPIO_ReadPin(GPIO_PORT_COLEND, GPIO_PIN_COLEND);
}

void characterMapSize_property_get(uint8_t *buf)
{
    buf[0] = SYMBOL_CNT;
}

void characterMap_property_set(uint8_t *buf)
{
    memcpy(openflap_ctx->config.symbol_set, buf, 4 * SYMBOL_CNT);
    openflap_ctx->store_config = true;
}
void characterMap_property_get(uint8_t *buf)
{
    memcpy(buf, openflap_ctx->config.symbol_set, 4 * SYMBOL_CNT);
}

void offset_property_set(uint8_t *buf)
{
    openflap_ctx->config.encoder_offset = buf[0];
    openflap_ctx->store_config = true;
}
void offset_property_get(uint8_t *buf)
{
    buf[0] = openflap_ctx->config.encoder_offset;
}

void vtrim_property_set(uint8_t *buf)
{
    openflap_ctx->config.vtrim = buf[0];
    openflap_ctx->store_config = true;
}
void vtrim_property_get(uint8_t *buf)
{
    buf[0] = openflap_ctx->config.vtrim;
}

void character_property_set(uint8_t *buf)
{
    openflap_ctx->flap_setpoint = buf[0];
}

void character_property_get(uint8_t *buf)
{
    buf[0] = openflap_ctx->flap_position;
}

void baseSpeed_property_set(uint8_t *buf)
{
    openflap_ctx->config.base_speed = buf[0];
    openflap_ctx->store_config = true;
}

void baseSpeed_property_get(uint8_t *buf)
{
    buf[0] = openflap_ctx->config.base_speed;
}

void propertyHandlersInit(openflap_ctx_t *ctx)
{
    openflap_ctx = ctx;

    openflap_ctx->chain_ctx.property_handler[firmware_property].set = firmware_property_set;
    openflap_ctx->chain_ctx.property_handler[firmware_property].get = NULL;

    openflap_ctx->chain_ctx.property_handler[command_property].set = command_property_set;
    openflap_ctx->chain_ctx.property_handler[command_property].get = NULL;

    openflap_ctx->chain_ctx.property_handler[columnEnd_property].set = NULL;
    openflap_ctx->chain_ctx.property_handler[columnEnd_property].get = columnEnd_property_get;

    openflap_ctx->chain_ctx.property_handler[characterMapSize_property].set = NULL;
    openflap_ctx->chain_ctx.property_handler[characterMapSize_property].get = characterMapSize_property_get;

    openflap_ctx->chain_ctx.property_handler[offset_property].get = offset_property_get;
    openflap_ctx->chain_ctx.property_handler[offset_property].set = offset_property_set;

    openflap_ctx->chain_ctx.property_handler[vtrim_property].set = vtrim_property_set;
    openflap_ctx->chain_ctx.property_handler[vtrim_property].get = vtrim_property_get;

    openflap_ctx->chain_ctx.property_handler[characterMap_property].set = characterMap_property_set;
    openflap_ctx->chain_ctx.property_handler[characterMap_property].get = characterMap_property_get;

    openflap_ctx->chain_ctx.property_handler[character_property].set = character_property_set;
    openflap_ctx->chain_ctx.property_handler[character_property].get = character_property_get;

    openflap_ctx->chain_ctx.property_handler[baseSpeed_property].set = baseSpeed_property_set;
    openflap_ctx->chain_ctx.property_handler[baseSpeed_property].get = baseSpeed_property_get;
}
