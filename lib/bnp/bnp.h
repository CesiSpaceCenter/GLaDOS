#ifndef BNP_BNP_H
#define BNP_BNP_H

#include <freertos_hooks.h>
#include <STM32FreeRTOS.h>
#include "hal/i2c.h"
#include "hal/spi.h"
#include "hal/uart.h"


namespace bnp {
    inline I2CManager i2c;
    inline SPIManager spi;
    inline UARTManager uart;

    void panic(const char*);
    void reset();
    void init();
    void sleep(long msecs);
    void jump_to_bootloader(void);
};

#endif
