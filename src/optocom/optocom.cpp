#include "optocom.h"


racer::optocom::State racer::optocom::remote_state = BOOTING;

uint8_t racer::optocom::pin = PIN_UART1_RX;

bnp::DigitalInput racer::optocom::optocom(pin, false, INPUT_PULLDOWN);

void racer::optocom::init() {
    optocom.begin();
}

void racer::optocom::task(void *arg) {
    while (true) {
        int t = pulseIn(pin, HIGH);
        int state = (int)round(500000.0/t);

        switch (state) {
            case 3:
                remote_state = STANDBY;
                break;
            case 6:
                remote_state = ARMED;
                break;
            case 9:
                remote_state = ASCENT;
                break;
            case 12:
                remote_state = DESCENT;
        }

        bnp::sleep(500);
    }
}