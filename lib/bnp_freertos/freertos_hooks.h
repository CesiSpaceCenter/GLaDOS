#ifndef BNP_FREERTOS_HOOKS_H
#define BNP_FREERTOS_HOOKS_H

#include <Arduino.h>

#ifdef __cplusplus
extern "C" {
#endif

void vApplicationStackOverflowHook(void* pxTask, char* pcTaskName);

#ifdef __cplusplus
}
#endif

#endif
