#include "bar.h"

racer::sensors::bar::BARData racer::sensors::bar::data;

Dps3xx racer::sensors::bar::bar;

void racer::sensors::bar::init() {
    bar.begin(*bnp::i2c[BAR_I2C_INSTANCE], 0x76);
    int ret = bar.measureTempOnce(data.temperature, 7);

    if (ret != 0) {
        bnp::panic("failed to init BAR");
    }
}

void racer::sensors::bar::read() {
    if (bar.measureTempOnce(data.temperature, 3) != 0) {
        bnp::panic("failed to get temp from BAR");
    }
    if (bar.measurePressureOnce(data.pressure, 7) != 0) {
        bnp::panic("failed to get pres from BAR");
    }
}