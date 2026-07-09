#include "hooks.h"

#include <Arduino.h>

void vApplicationStackOverflowHook(void* pxTask, char* pcTaskName) {
    __disable_irq();

    Serial.print("stack overflowed on task ");
    Serial.println(pcTaskName);

    while(1);
}
