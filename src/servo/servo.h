#ifndef _RACER_SERVO_H
#define _RACER_SERVO_H

#include <bnp.h>
#include <hal/digitalOutput.h>
#include <Servo.h>

namespace racer::servo {
  Servo servo;

  extern bnp::DigitalOutput power;

  void init();
  void move(int targetPos);
}

#endif
