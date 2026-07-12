#include "led.h"
#include "state.h"

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
        switch (state::current_state) {
        case state::BOOTING:
            blink(50, 300);
            break;
        case state::STANDBY:
            blink(50, 100);
            blink(50, 2000);
            break;
        case state::ARMED:
            blink(100, 50);
            blink(2000, 50);
            break;
        case state::ASCENT:
            blink(500, 500);
            break;
        case state::DESCENT:
            blink(1000, 1000);
            break;
        }
    }
}