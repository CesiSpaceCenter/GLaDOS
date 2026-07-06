#ifndef _RACER_TM_H
#define _RACER_TM_H

#include "bnp.h"
#include "sensors/sensors.h"
#include "ahrs.h"

static void tm_task(void* arg) {
    UNUSED(arg);
    int16_t mx, my, mz;
    while (true) {
        bnp::sleep(500);
        Serial.print(">t:"); Serial.println(millis());

        Serial.print(">pitch:"); Serial.println(ahrs_data.pitch);
        Serial.print(">roll:"); Serial.println(ahrs_data.roll);
        Serial.print(">yaw:"); Serial.println(ahrs_data.yaw);

        Serial.print(">accx:"); Serial.println(imu_data.ax);
        Serial.print(">accy:"); Serial.println(imu_data.ay);
        Serial.print(">accz:"); Serial.println(imu_data.az);

        /*mag.getHeading(&mx, &my, &mz);
        Serial.print(">magX:"); Serial.println(mx);
        Serial.print(">magY:"); Serial.println(my);
        Serial.print(">magZ:"); Serial.println(mz);*/

        Serial.print(">pres:"); Serial.println(bar_data.pressure);
        Serial.print(">temp:"); Serial.println(bar_data.temperature);

        Serial.print(">vbat:"); Serial.println(voltage / 35300.0 * 20.1);
        Serial.print(">vref:"); Serial.println(mcu_data.vref);
        Serial.print(">mcu_temp:"); Serial.println(mcu_data.temperature);
        Serial.print(">optocom:"); Serial.println(digitalRead(PIN_UART2_RX));
    }
}

#endif _RACER_TM_H