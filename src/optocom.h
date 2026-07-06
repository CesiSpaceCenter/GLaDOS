#ifndef _RACER_OPTOCOM_H
#define _RACER_OPTOCOM_H

#include <bnp.h>
#include <drivers/digitalInput.h>

enum State {
    BOOTING = 0,
    STANDBY = 3,
    ARMED = 6,
    ASCENT = 9,
    DESCENT = 12,
    LANDED
};
State scu_state = BOOTING;

bnp::DigitalInput optocom(PIN_UART1_RX, false, INPUT_PULLDOWN);

void optocom_init() {
  optocom.begin();
}

static void optocom_task(void *arg) {
    while (true) {
        int t = pulseIn(PIN_UART1_RX, HIGH);
        int state = (int)round(500000.0/t);

        switch (state) {
            case 3:
                scu_state = STANDBY;
                break;
            case 6:
                scu_state = ARMED;
                break;
            case 9:
                scu_state = ASCENT;
                break;
            case 12:
                scu_state = DESCENT;
        }

        bnp::sleep(500);
    }
}

#endif
