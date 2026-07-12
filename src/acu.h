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
#include "screen/screen.h"
#include "optocom/optocom.h"

using namespace racer;

bnp::DigitalOutput camera_power(PIN_IO1, LOW, true);

static void main_task(void *arg) {
  UNUSED(arg);
  while (true) {
    bnp::sleep(1000/20);
  }
}

void setup() {
  bnp::sleep(1000);
  bnp::init();
  BNP_LOG("bnp init ok - acu");
  bnp::sleep(100);

  camera_power.begin();

  bnp::sleep(100);

  racer::led::init();
  racer::blackbox::init();
  racer::sensors::init();
  racer::ahrs::init();
  racer::servo::init();
  racer::screen::init();
  racer::optocom::init();

  bnp::freertos::create_task(racer::cmd::task, 1, "cmd");
  bnp::freertos::create_task(racer::led::task, 1, "led");
  bnp::freertos::create_task(racer::sensors::task, 1, "sensors");
  bnp::freertos::create_task(racer::screen::task, 1, "screen");
  bnp::freertos::create_task(racer::optocom::task, 1, "optocom");
  bnp::freertos::create_task(racer::ahrs::task, 1, "ahrs");
  //bnp::freertos::create_task(main_task, 2, "main");
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
