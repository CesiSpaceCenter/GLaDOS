#include <Arduino.h>
#include <bnp.h>
#include <log.h>
#include <drivers/digitalInput.h>
#include <drivers/digitalOutput.h>
#include <hal/board.h>
#include <freertos_utils.h>

#include "ahrs.h"
#include "led.h"
#include "sensors/sensors.h"
#include "tm.h"
#include "cmd.h"


// ACU
bnp::DigitalOutput cameraPower(PIN_IO1, LOW, true);

static void mainThread(void *arg) {
  UNUSED(arg);
  while (true) {
    bnp::sleep(1000);
    BNP_LOG("{}, bar:{:.7}", millis(), bar_data.pressure);

  }
}

void setup() {
  bnp::sleep(1000);
  bnp::init();
  BNP_LOG("bnp init ok - acu");
  bnp::sleep(100);
  led.begin();
  //cameraPower.begin();

  bnp::sleep(100);

  led_init();
  sensors_init();
  ahrs_init();

  bnp::freertos::create_task(cmd_task, 1, "cmd");
  bnp::freertos::create_task(led_task, 1, "led");
  bnp::freertos::create_task(sensors_task, 1, "sensors");
  bnp::freertos::create_task(mainThread, 2, "main");
  bnp::freertos::create_task(ahrs_task, 1, "ahrs");
  bnp::freertos::create_task(tm_task, 2, "tm");

  BNP_LOG("init ok");

  vTaskStartScheduler();
  bnp::panic("Not enough RAM");
}

void loop() {}
