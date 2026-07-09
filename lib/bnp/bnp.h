#ifndef BNP_BNP_H
#define BNP_BNP_H

#include "bnp_config.h"
#include <freertos/hooks.h>
#include <STM32FreeRTOS.h>
#include "hal/i2c.h"
#include "hal/spi.h"
#include "hal/uart.h"

#include <string>

namespace bnp {
    inline I2CManager i2c;
    inline SPIManager spi;
    inline UARTManager uart;

    void panic(const char*);
    void panic(std::string);
    void reset();
    void init();
    void sleep(long msecs);
    void jump_to_bootloader(void);
};

#endif
