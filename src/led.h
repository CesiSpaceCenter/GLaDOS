#ifndef _RACER_LED_H
#define _RACER_LED_H

#include <bnp.h>
#include <drivers/digitalOutput.h>
#include "optocom.h"

bnp::DigitalOutput led(PIN_LED, LOW, true);
bnp::DigitalOutput cipLed(PIN_S6, HIGH, false);

void led_init() {
  led.begin();
  cipLed.begin();
}

void led_blink(int on_time, int off_time) {
  led.on();
  cipLed.on();
  bnp::sleep(on_time);

  led.off();
  cipLed.off();
  bnp::sleep(off_time);

}

static void led_task(void *arg) {
  UNUSED(arg);
  while (true) {
    switch (scu_state) {
      case BOOTING:
        led_blink(50, 300);
        break;
      case STANDBY:
        led_blink(50, 100);
        led_blink(50, 2000);
        break;
      case ARMED:
        led_blink(100, 50);
        led_blink(2000, 50);
        break;
      case ASCENT:
        led_blink(500, 500);
        break;
      case DESCENT:
        led_blink(1000, 1000);
        break;

    }
  }
}

#endif
