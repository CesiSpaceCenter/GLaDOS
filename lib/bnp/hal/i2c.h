#ifndef BNP_I2C_H
#define BNP_I2C_H

#include <Wire.h>
#include "board.h"

namespace bnp {
    const int num_i2c_buses = 3;
    class I2CManager {
    public:
        void init();
        TwoWire* operator[](int index);

    private:
        TwoWire* i2c_buses[num_i2c_buses] = {
            #if I2C1_ENABLE
            new TwoWire(PIN_I2C1_SDA, PIN_I2C1_SCL),
            #else
            nullptr,
            #endif

            #if I2C2_ENABLE
            new TwoWire(PIN_I2C2_SDA, PIN_I2C2_SCL),
            #else
            nullptr,
            #endif

            #if I2C3_ENABLE
            new TwoWire(PIN_I2C3_SDA, PIN_I2C3_SCL),
            #else
            nullptr,
            #endif
        };
    };
};

#endif