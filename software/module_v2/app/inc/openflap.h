#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "py32f0xx_hal.h"

/** The number of flaps in the split flap module. */
#define SYMBOL_CNT (48)

/** The number of IR sensors. */
#define SENS_CNT (6)

/** Map sensor adc channel to bit in encoder byte:
 *  - Bit 0 <-- ADC channel 2
 *  - Bit 1 <-- ADC channel 3
 *  - Bit 2 <-- ADC channel 1
 *  - Bit 3 <-- ADC channel 4
 *  - Bit 4 <-- ADC channel 0
 *  - Bit 5 <-- ADC channel 5
 */
#define IR_MAP ((uint8_t[]){2, 3, 1, 4, 0, 5})

#define GPIO_PIN_LED GPIO_PIN_7
#define GPIO_PORT_LED GPIOA
#define GPIO_PIN_MOTOR GPIO_PIN_6
#define GPIO_PORT_MOTOR GPIOA

/** Sensor threshold values. */
typedef struct ir_sens_threshold_tag {
    uint16_t ir_low;
    uint16_t ir_high;
} ir_sens_threshold_t;

/** Configuration data for NVM storage. */
typedef struct openflap_config_tag {
    uint8_t encoder_offset;                  /**< Offset of the encoder compared to the actual symbol index. */
    ir_sens_threshold_t ir_limits[SENS_CNT]; /**< Sensor thresholds for each IR sensor. */
    uint8_t vtrim;                           /**< Virtual trim setting. */
    uint8_t base_speed;                      /**< Base speed of the flap wheel. */
    uint8_t symbol_set[4 * SYMBOL_CNT];      /**< An array of all supported symbols. */
} openflap_config_t;

/** Struct with helper variables. */
typedef struct openflap_ctx_tag {
    uint8_t flap_position; /**< The current position of flap wheel. */
    uint8_t flap_setpoint; /**< The desired position of flap wheel. */
} openflap_ctx_t;
