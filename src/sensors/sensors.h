#ifndef _RACER_SENSORS_H
#define _RACER_SENSORS_H

#include <bnp.h>
#include <drivers/analogInput.h>
#include <hal/board.h>
#include <log.h>
#include <STM32FreeRTOS.h>
//#include <AK8975.h>

namespace racer::sensors {
    //AK8975 mag(0x0d);
    extern bnp::AnalogInput vbat;
    extern float voltage;

    void init();
    void task(void*);
}

#endif
