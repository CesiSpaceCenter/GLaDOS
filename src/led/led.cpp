#include "led.h"
#include "optocom/optocom.h"

bnp::DigitalOutput racer::led::led(PIN_LED, LOW, true);
bnp::DigitalOutput racer::led::cip_led(PIN_S6, HIGH, false);

void racer::led::init() {
    led.begin();
    cip_led.begin();
}

void racer::led::blink(int on_time, int off_time) {
    led.on();
    cip_led.on();
    bnp::sleep(on_time);

    led.off();
    cip_led.off();
    bnp::sleep(off_time);
}

void racer::led::task(void *arg) {
    UNUSED(arg);
    while (true) {
        switch (optocom::remote_state) {
        case optocom::State::BOOTING:
            blink(50, 300);
            break;
        case optocom::State::STANDBY:
            blink(50, 100);
            blink(50, 2000);
            break;
        case optocom::State::ARMED:
            blink(100, 50);
            blink(2000, 50);
            break;
        case optocom::State::ASCENT:
            blink(500, 500);
            break;
        case optocom::State::DESCENT:
            blink(1000, 1000);
            break;
        }
    }
}