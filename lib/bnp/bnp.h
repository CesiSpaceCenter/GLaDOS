#ifndef BNP_BNP_H
#define BNP_BNP_H

#include "hal/i2c.h"
#include "hal/spi.h"
#include "hal/uart.h"
#include <STM32FreeRTOS.h>

namespace bnp {
    inline I2CManager i2c;
    inline SPIManager spi;
    inline UARTManager uart;

    void panic(const char*);
    void reset();
    void init();
    void sleep(long msecs);
    void create_task(TaskFunction_t func, UBaseType_t priority, const char* name);
};

#endif
