#ifndef _RACER_SENSORS_BAR_H
#define _RACER_SENSORS_BAR_H

#include <bnp.h>
#include <Dps3xx.h>

namespace racer::sensors::bar {
    struct BARData
    {
        float temperature;
        float pressure;
    };
    extern BARData data;

    extern Dps3xx bar;

    void init();
    void read();
}

#endif
