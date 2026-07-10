#include <Arduino.h>
#include <bnp.h>
#include <log.h>
#include <hal/digitalInput.h>
#include <hal/digitalOutput.h>
#include <freertos/utils.h>
#include <IWatchdog.h>

#include "ahrs/ahrs.h"
#include "led/led.h"
#include "sensors/sensors.h"
#include "sensors/bar.h"
#include "tm/tm.h"
#include "cmd/cmd.h"
#include "blackbox/blackbox.h"

// ACU
bnp::DigitalOutput camera_power(PIN_IO1, LOW, true);

static void mainThread(void *arg) {
  UNUSED(arg);
  while (true) {
    bnp::sleep(1000);
    BNP_LOG("{}, bar:{:.7}", millis(), racer::sensors::bar::data.pressure);

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

  bnp::freertos::create_task(racer::cmd::task, 1, "cmd");
  bnp::freertos::create_task(racer::led::task, 1, "led");
  bnp::freertos::create_task(racer::sensors::task, 1, "sensors");
  bnp::freertos::create_task(mainThread, 2, "main");
  bnp::freertos::create_task(racer::ahrs::task, 1, "ahrs");
  //bnp::freertos::create_task(racer::tm::task, 2, "tm");

  BNP_LOG("init ok");

  vTaskStartScheduler();
  bnp::panic("not enough RAM");
}

void loop() {
  IWatchdog.reload();
  bnp::sleep(2000);
}
