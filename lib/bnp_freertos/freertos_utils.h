#ifndef BNP_FREERTOS_UTILS_H
#define BNP_FREERTOS_UTILS_H

#include <STM32FreeRTOS.h>

namespace bnp::freertos {
    void create_task(TaskFunction_t func, UBaseType_t priority, const char* name);
}

#endif
