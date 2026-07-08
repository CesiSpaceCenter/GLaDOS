#ifndef _RACER_SENSORS_MCU_H
#define _RACER_SENSORS_MCU_H

#include <bnp.h>
#include "stm32yyxx_ll_adc.h"

// from https://github.com/stm32duino/STM32Examples/blob/main/examples/Peripherals/ADC/Internal_channels/Internal_channels.ino

namespace racer::sensors::mcu {
  #ifdef AVREF
  static uint32_t readVref();
  #endif

  #ifdef ATEMP
  static int32_t readTempSensor(int32_t VRef);
  #endif

  struct MCUData
  {
      float temperature;
      float vref;
  };
  extern MCUData data;

  void read();
}

#endif