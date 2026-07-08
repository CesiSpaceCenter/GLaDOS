#include "imu.h"

racer::sensors::imu::IMUData racer::sensors::imu::data;
racer::sensors::imu::IMUData racer::sensors::imu::calib = {
    .gx = 1,
    .gy = 2,
    .gz = 1,
    .ax = -0.0069,
    .ay = -0.0013,
    .az = 1,
};

racer::sensors::imu::IMUData racer::sensors::imu::sum_data;
racer::sensors::imu::IMUData racer::sensors::imu::last_data;

ICM42688 racer::sensors::imu::imu(*bnp::spi[GYRO_SPI], PIN_GYRO_2_CS);

void racer::sensors::imu::init() {
    if (imu.begin() < 0) {
		bnp::panic("failed to init IMU");
	}

    if (imu.setAccelODR(ICM42688::odr200) < 0 || imu.setGyroODR(ICM42688::odr200) < 0) {
        bnp::panic("failed to set IMU parameters");
    }
}

void racer::sensors::imu::read() {
    if (imu.getAGT() >= 0) {
        last_data = data;
        data.ax = imu.accX();
        data.ay = imu.accY();
        data.az = imu.accZ();
        data.gx = imu.gyrX();
        data.gy = imu.gyrY();
        data.gz = imu.gyrZ();
    } else {
        bnp::panic("failed to get AGT from IMU");
    }
}