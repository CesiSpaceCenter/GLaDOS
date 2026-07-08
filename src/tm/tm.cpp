#include "tm.h"
#include "bnp.h"
#include "sensors/sensors.h"
#include "sensors/imu.h"
#include "sensors/bar.h"
#include "sensors/mcu.h"
#include "ahrs/ahrs.h"

void racer::tm::task(void* arg) {
    UNUSED(arg);
    int16_t mx, my, mz;
    while (true) {
        bnp::sleep(500);
        Serial.print(">t:"); Serial.println(millis());

        Serial.print(">pitch:"); Serial.println(ahrs::data.pitch);
        Serial.print(">roll:"); Serial.println(ahrs::data.roll);
        Serial.print(">yaw:"); Serial.println(ahrs::data.yaw);

        Serial.print(">accx:"); Serial.println(sensors::imu::data.ax);
        Serial.print(">accy:"); Serial.println(sensors::imu::data.ay);
        Serial.print(">accz:"); Serial.println(sensors::imu::data.az);

        /*mag.getHeading(&mx, &my, &mz);
        Serial.print(">magX:"); Serial.println(mx);
        Serial.print(">magY:"); Serial.println(my);
        Serial.print(">magZ:"); Serial.println(mz);*/

        Serial.print(">pres:"); Serial.println(sensors::bar::data.pressure);
        Serial.print(">temp:"); Serial.println(sensors::bar::data.temperature);

        Serial.print(">vbat:"); Serial.println(sensors::voltage / 35300.0 * 20.1);
        Serial.print(">vref:"); Serial.println(sensors::mcu::data.vref);
        Serial.print(">mcu_temp:"); Serial.println(sensors::mcu::data.temperature);
        Serial.print(">optocom:"); Serial.println(digitalRead(PIN_UART2_RX));
    }
}