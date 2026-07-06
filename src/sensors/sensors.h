#ifndef _RACER_SENSORS_H
#define _RACER_SENSORS_H

#include <bnp.h>
#include <drivers/analogInput.h>
#include <hal/board.h>
#include <STM32FreeRTOS.h>
#include "bar.h"
#include "imu.h"
#include "mcu.h"
//#include <AK8975.h>

//AK8975 mag(0x0d);

bnp::AnalogInput vbat(PIN_ADC_VBAT);
float voltage;

void sensors_init() {
    //imu_init();
    bar_init();
    vbat.begin();
    /*mag.initialize();
    if (!mag.testConnection()) {
        bnp::panic("failed to init MAG");
    }*/
}

void sensors_task(void* arg) {
    UNUSED(arg);
    while (true) {
        //imu_read();
        bar_read();
        mcu_read();
        voltage = vbat.get() / 35300.0 * 19.07;
        bnp::sleep(1000/200);
    }
}

#endif
