#include "sensors.h"

#include "bar.h"
#include "imu.h"
#include "mcu.h"

bnp::AnalogInput racer::sensors::vbat(PIN_ADC_VBAT);

float racer::sensors::voltage;

void racer::sensors::init() {
    BNP_LOG("initializing sensors");
    imu::init();
    bar::init();
    vbat.begin();
    BNP_LOG("initialized sensors");
}

void racer::sensors::task(void* arg) {
    UNUSED(arg);
    while (true) {
        imu::read();
        bar::read();
        mcu::read();
        voltage = vbat.get() / 35300.0 * 19.07;
        bnp::sleep(1000/200);
    }
}