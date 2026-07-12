#ifndef _RACER_OPTOCOM_H
#define _RACER_OPTOCOM_H

#include "state.h"
#include <bnp.h>
#include <hal/digitalInput.h>

namespace racer::optocom {
    extern uint8_t pin;
    extern bnp::DigitalInput optocom;

    void init();
    void task(void *);
}

#endif
