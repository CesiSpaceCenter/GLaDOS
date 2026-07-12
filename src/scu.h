#include <Arduino.h>
#include <bnp.h>
#include <log.h>
#include <hal/digitalInput.h>
#include <hal/digitalOutput.h>
#include <hal/PWMOutput.h>
#include <freertos/utils.h>
#include <IWatchdog.h>

#include "state.h"
#include "ahrs/ahrs.h"
#include "led/led.h"
#include "sensors/sensors.h"
#include "servo/servo.h"
#include "cmd/cmd.h"
#include "blackbox/blackbox.h"

using namespace racer;

bnp::PWMOutput optocom_out(PIN_S5);
bnp::DigitalOutput beeper(PIN_BEEPER, HIGH, true);
bnp::DigitalInput jack(PIN_UART5_TX, true, INPUT_PULLUP);
bnp::DigitalInput arm(PIN_S7, false, INPUT_PULLUP);

static void main_task(void *arg) {
  UNUSED(arg);
  while (true) {
    bnp::sleep(1000/20);
    switch (state::current_state) {
    case state::STANDBY:
      if (arm.is_on()) {
        if (jack.is_on()) {
          state::current_state = state::ARMED;
          racer::servo::move(160);
          BNP_LOG("switch to mode armed");
          tone(PIN_BEEPER, 800);
          bnp::sleep(1000);
          noTone(PIN_BEEPER);
          tone(PIN_S5, 6);
        } else {
          BNP_LOG("Cannot switch to ARMED, jack is not plugged in");
          racer::servo::move(70);
          bnp::sleep(100);
        }
      }
      break;
    case state::ARMED:
      if (arm.is_off()) {
        state::current_state = state::STANDBY;
        BNP_LOG("switch back to mode standby");
        tone(PIN_S5, 3);
        break;
      }
      if (jack.is_off()) {
        tone(PIN_S5, 9);
        state::current_state = state::ASCENT;
        BNP_LOG("liftoff");
        bnp::sleep(20000);
        BNP_LOG("apogee");
        tone(PIN_S5, 12);
        racer::servo::move(1);
        state::current_state = state::DESCENT;
        bnp::sleep(20000);
        tone(PIN_BEEPER, 800);
      }
      break;
    }
  }
}

void setup() {
  bnp::sleep(1000);
  bnp::init();
  BNP_LOG("bnp init ok - scu");
  bnp::sleep(100);

  beeper.begin();
  arm.begin();
  jack.begin();
  optocom_out.begin();

  bnp::sleep(100);

  racer::led::init();
  racer::blackbox::init();
  racer::sensors::init();
  racer::ahrs::init();
  racer::servo::init();

  tone(PIN_S5, 3);

  bnp::freertos::create_task(racer::cmd::task, 1, "cmd");
  bnp::freertos::create_task(racer::led::task, 1, "led");
  bnp::freertos::create_task(racer::sensors::task, 1, "sensors");
  bnp::freertos::create_task(racer::ahrs::task, 1, "ahrs");
  bnp::freertos::create_task(main_task, 2, "main");
  //bnp::freertos::create_task(racer::tm::task, 2, "tm");

  state::current_state = state::STANDBY;

  BNP_LOG("init ok");


  vTaskStartScheduler();
  bnp::panic("not enough RAM");
}

void loop() {
  IWatchdog.reload();
  delay(2000);
}
