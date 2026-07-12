#include "optocom.h"
#include "state.h"
#include <log.h>


uint8_t racer::optocom::pin = PIN_UART1_RX;

bnp::DigitalInput racer::optocom::optocom(pin, false, INPUT_PULLDOWN);

void racer::optocom::init() {
    optocom.begin();
}

void racer::optocom::task(void *arg) {
    while (true) {
        int t = pulseIn(pin, HIGH);
        int state = (int)round(500000.0/t);
        BNP_LOG("scu state = {}", t);
        switch (state) {
            case 3:
                state::remote_state = racer::state::STANDBY;
                break;
            case 6:
                state::remote_state = racer::state::ARMED;
                break;
            case 9:
                state::remote_state = racer::state::ASCENT;
                break;
            case 12:
                state::remote_state = racer::state::DESCENT;
        }

        bnp::sleep(500);
    }
}