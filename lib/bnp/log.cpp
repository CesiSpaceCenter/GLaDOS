#include "log.h"
#include <FreeRTOSConfig.h>
void bnp::log::init() { bnp::log::mutex = xSemaphoreCreateMutex(); }


