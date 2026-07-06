#ifndef _RACER_AHRS_H
#define _RACER_AHRS_H

#include "sensors/sensors.h"
#include <MadgwickAHRS.h>
#include <STM32FreeRTOS.h>

Madgwick filter;

struct AHRSData
{
    float roll;
    float pitch;
    float yaw;
} inline ahrs_data;


void ahrs_init() {
    filter.begin(200);
}

void ahrs_task(void* arg) {
    UNUSED(arg);
    while (true) {
        filter.updateIMU(
            imu_data.gx, imu_data.gy, imu_data.gz,
            imu_data.ax, imu_data.ay, imu_data.az
        );

        ahrs_data.roll = filter.getRoll();
        ahrs_data.pitch = filter.getPitch();
        ahrs_data.yaw = filter.getYaw();

        bnp::sleep(1000/200);
    }
}

#endif
