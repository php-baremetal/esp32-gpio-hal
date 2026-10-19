# esp32-gpio-hal

The ESP32 side of [ext-gpio](package:php-baremetal/ext-gpio): it implements the neutral GPIO HAL
(`bm_gpio_hal.h`, shipped by ext-gpio) over the ESP-IDF GPIO driver. It adds no PHP API of its own.

| Property | Value |
| --- | --- |
| Type | `bm-hal` |
| Platform | `esp32` (`extra.baremetal.platform`) |
| Provides | `php-baremetal/gpio-hal` |
| Requires | nothing |
| ESP-IDF components (`idf-requires`) | `esp_driver_gpio` |

## Install

You do not require it. ext-gpio requires the virtual `php-baremetal/gpio-hal`, and conductor adds this package
when the project's SDK is on the `esp32` platform (`"sdk": "esp32@^1.0"`). Require the extension:

```bash
composer require php-baremetal/ext-gpio
```

The functions are documented in [ext-gpio](package:php-baremetal/ext-gpio#docs/overview.md).

## What it does on ESP32

| HAL call | ESP-IDF |
| --- | --- |
| mode (behind `gpio_mode()`) | `gpio_reset_pin()`, then `gpio_set_direction()` with `GPIO_MODE_INPUT_OUTPUT` for an output or `GPIO_MODE_INPUT` for an input |
| write (behind `gpio_write()`) | `gpio_set_level()` with 0 or 1 |
| read (behind `gpio_read()`) | `gpio_get_level()` |

What users notice:

- `gpio_reset_pin()` enables the pin's internal pull-up and detaches any peripheral, so every `gpio_mode()` call
  leaves the pull-up on and takes the pin away from whatever used it before.
- Outputs are input-and-output, so reading an output returns the driven level.
- Pin numbers are not checked before the call. ESP-IDF rejects an invalid one with an error on the console; PHP
  sees no error.
- Every call runs directly on the calling task; nothing goes through the executor.

## License

MIT.
