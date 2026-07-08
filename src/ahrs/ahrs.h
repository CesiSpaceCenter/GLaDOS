#ifndef _RACER_AHRS_H
#define _RACER_AHRS_H

#include <MadgwickAHRS.h>


namespace racer::ahrs {
    extern Madgwick filter;

    struct AHRSData
    {
        float roll;
        float pitch;
        float yaw;
    };

    extern AHRSData data;

    void init();
    void task(void*);
}


#endif
