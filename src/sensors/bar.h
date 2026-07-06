#ifndef _RACER_SENSORS_BAR_H
#define _RACER_SENSORS_BAR_H

#include <bnp.h>
#include <Dps3xx.h>

struct BARData
{
    float temperature;
    float pressure;
};
BARData bar_data;

Dps3xx bar;

void bar_init() {
    bar.begin(*bnp::i2c[BAR_I2C_INSTANCE], 0x76);
    int ret = bar.measureTempOnce(bar_data.temperature, 7);

    if (ret != 0) {
        bnp::panic("failed to init BAR");
    }
}

void bar_read() {
    if (bar.measureTempOnce(bar_data.temperature, 3) != 0) {
        bnp::panic("failed to get temp from BAR");
    }
    if (bar.measurePressureOnce(bar_data.pressure, 7) != 0) {
        bnp::panic("failed to get pres from BAR");
    }
}

#endif
