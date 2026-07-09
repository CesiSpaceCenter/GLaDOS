#ifndef _RACER_LED_H
#define _RACER_LED_H

#include <bnp.h>
#include <hal/digitalOutput.h>

namespace racer::led {
  extern bnp::DigitalOutput led;
  extern bnp::DigitalOutput cip_led;

  void init();
  void blink(int on_time, int off_time);
  void task(void *arg);
}

#endif
