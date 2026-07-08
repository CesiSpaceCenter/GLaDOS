#ifndef _RACER_OPTOCOM_H
#define _RACER_OPTOCOM_H

#include "hal/boards/DFR_F722_DUAL_HD.h"
#include <bnp.h>
#include <drivers/digitalInput.h>

namespace racer::optocom {
    extern uint8_t pin;
    extern bnp::DigitalInput optocom;
    
    enum State {
        BOOTING = 0,
        STANDBY = 3,
        ARMED = 6,
        ASCENT = 9,
        DESCENT = 12,
        LANDED
    };
    extern State remote_state;

    void init();
    void task(void *);
}

#endif
