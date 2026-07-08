#ifndef _RACER_SENSORS_IMU_H
#define _RACER_SENSORS_IMU_H

#include <bnp.h>
#include <ICM42688.h>

struct IMUData
{
    float gx;
    float gy;
    float gz;
    float ax;
    float ay;
    float az;
};

IMUData imu_data;
IMUData imu_calib = {
    .gx = 1,
    .gy = 2,
    .gz = 1,
    .ax = -0.0069,
    .ay = -0.0013,
    .az = 1,
};

IMUData sum_imu_data;
IMUData last_imu_data;

ICM42688 imu(*bnp::spi[GYRO_SPI], PIN_GYRO_2_CS);

void imu_init() {
    if (imu.begin() < 0) {
		bnp::panic("failed to init IMU");
	}

    if (imu.setAccelODR(ICM42688::odr200) < 0 || imu.setGyroODR(ICM42688::odr200) < 0) {
        bnp::panic("failed to set IMU parameters");
    }
}

void imu_read() {
    if (imu.getAGT() >= 0) {
        last_imu_data = imu_data;
        imu_data.ax = imu.accX();
        imu_data.ay = imu.accY();
        imu_data.az = imu.accZ();
        imu_data.gx = imu.gyrX();
        imu_data.gy = imu.gyrY();
        imu_data.gz = imu.gyrZ();
    } else {
        bnp::panic("failed to get AGT from IMU");
    }
}

#endif
