#include "freertos_utils.h"
#include <Arduino.h>

void bnp::freertos::create_task(TaskFunction_t func, UBaseType_t priority, const char* name) {
    portBASE_TYPE s = xTaskCreate(func, name, 2048, NULL, priority, NULL);
    if (s != pdPASS) {
        Serial.print("could not start task");
        Serial.println(name);
        while(1);
    }
}
