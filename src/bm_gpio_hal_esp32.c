/*
   +----------------------------------------------------------------------+
   | php-baremetal: esp32-gpio-hal                                        |
   +----------------------------------------------------------------------+
   | Copyright (c) 2026 Gianfrancesco Aurecchia                           |
   +----------------------------------------------------------------------+
   | This source file is subject to the MIT license, that is bundled with |
   | this package in the file LICENSE.                                    |
   +----------------------------------------------------------------------+
   | Authors: Gianfrancesco Aurecchia <gianfri@aurecchia.com>             |
   +----------------------------------------------------------------------+
*/

/* ESP32 implementation of the GPIO HAL (bm_gpio_hal.h) over driver/gpio. */
#include "bm_gpio_hal.h"
#include "driver/gpio.h"

void bm_gpio_hal_mode(int pin, int output)
{
    gpio_reset_pin((gpio_num_t) pin);
    gpio_set_direction((gpio_num_t) pin, output ? GPIO_MODE_INPUT_OUTPUT : GPIO_MODE_INPUT);
}

void bm_gpio_hal_write(int pin, int level)
{
    gpio_set_level((gpio_num_t) pin, level ? 1 : 0);
}

int bm_gpio_hal_read(int pin)
{
    return gpio_get_level((gpio_num_t) pin);
}
