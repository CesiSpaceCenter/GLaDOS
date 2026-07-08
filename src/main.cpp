
#include <Arduino.h>
#include <bnp.h>
#include <hal/board.h>
#include <drivers/digitalOutput.h>
#include <hal/board.h>
#include <freertos_utils.h>
#include <log.h>

#include "sensors/sensors.h"
#include "ahrs.h"
#include "blackbox.h"
#include "tm.h"
#include "screen/screen.h"
#include "gnss.h"
#include "servo.h"
#include "led.h"
#include "optocom.h"
#include "cmd.h"

bnp::DigitalOutput servoPower(PIN_S4, HIGH, false);

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
    delay(2000);
    bnp::init();
    BNP_LOG("bnp init ok - acu");
    bnp::sleep(100);
    led.begin();
    servoPower.begin();
    cameraPower.begin();

    bnp::sleep(100);

    led_init();
    optocom_init();
    screen_init();
    sensors_init();
    ahrs_init();
    servo_init();
    //gnss_init();
    //blackbox_init();

  bnp::freertos::create_task(cmd_task, 1, "cmd");
  bnp::freertos::create_task(led_task, 1, "led");
  // bnp::freertos::create_task(screen_task,0, "screen");
  bnp::freertos::create_task(sensors_task, 1, "sensors");
  bnp::freertos::create_task(mainThread, 2, "main");
  // bnp::freertos::create_task(optocom_task, 0, "optocom");
  // bnp::freertos::create_task(gnss_task, 2, "gnss");
  bnp::freertos::create_task(ahrs_task, 1, "ahrs");
  bnp::freertos::create_task(tm_task, 2, "tm");
  // bnp::freertos::create_task(blackbox_task, 2, "blackbox");

  BNP_LOG("init ok");

    blackbox_print_all();

    vTaskStartScheduler();
    bnp::panic("Not enough RAM");
}

void loop() {
}
