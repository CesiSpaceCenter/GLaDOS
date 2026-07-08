#include "ahrs.h"
#include "sensors/imu.h"
#include <log.h>

Madgwick racer::ahrs::filter;
racer::ahrs::AHRSData racer::ahrs::data;

void racer::ahrs::init() {
    BNP_LOG("initializing");
    filter.begin(200);
}

void racer::ahrs::task(void* arg) {
    UNUSED(arg);
    while (true) {
        filter.updateIMU(
            sensors::imu::data.gx, sensors::imu::data.gy, sensors::imu::data.gz,
            sensors::imu::data.ax, sensors::imu::data.ay, sensors::imu::data.az
        );

        data.roll = filter.getRoll();
        data.pitch = filter.getPitch();
        data.yaw = filter.getYaw();

        bnp::sleep(1000/200);
    }
}