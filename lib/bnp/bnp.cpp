#include "bnp.h"
#include "hal/board.h"
#include <Arduino.h>

void bnp::panic(const char* message) {
    digitalWrite(PIN_LED, LOW);
    while (true) {
        if (Serial.available()) {
            bnp::reset();
        }
        Serial.println("---- PANIC ----");
        Serial.println(message);
        delay(1000);
    }
}

void bnp::reset() {
    NVIC_SystemReset();
}

void bnp::init() {
    pinMode(PIN_LED, OUTPUT);
    digitalWrite(PIN_LED, HIGH);
    Serial.begin(9600);
    Serial.println("bnp init");
    bnp::i2c.init();
    bnp::spi.init();
    bnp::uart.init();
}

void bnp::sleep(long msecs) {
    if (xTaskGetSchedulerState() == taskSCHEDULER_RUNNING) {
        vTaskDelay((msecs * configTICK_RATE_HZ) / 1000L);
    } else {
        delay(msecs);
    }
}

void bnp::create_task(TaskFunction_t func, UBaseType_t priority, const char* name) {
    portBASE_TYPE s = xTaskCreate(func, name, configMINIMAL_STACK_SIZE, NULL, priority, NULL);
    if (s != pdPASS) bnp::panic(strcat((char*)"Could not init task ", name));
}
