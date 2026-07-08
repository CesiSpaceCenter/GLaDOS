#ifndef _RACER_SENSORS_IMU_H
#define _RACER_SENSORS_IMU_H

#include <bnp.h>
#include <ICM42688.h>

namespace racer::sensors::imu {
    struct IMUData
    {
        float gx;
        float gy;
        float gz;
        float ax;
        float ay;
        float az;
    };

    extern IMUData data;
    extern IMUData calib;

    extern IMUData sum_data;
    extern IMUData last_data;

    extern ICM42688 imu;

    void init();
    void read();
}

#endif
