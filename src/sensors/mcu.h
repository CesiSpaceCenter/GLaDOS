#ifndef _RACER_SENSORS_MCU_H
#define _RACER_SENSORS_MCU_H

#include <bnp.h>
#include "stm32yyxx_ll_adc.h"

// from https://github.com/stm32duino/STM32Examples/blob/main/examples/Peripherals/ADC/Internal_channels/Internal_channels.ino

#ifdef AVREF
static uint32_t readVref() {
  uint32_t Vref = 3300;
#ifdef STM32U0xx
  /* On some devices Internal voltage reference calibration value not programmed
     during production and return 0xFFFF. See errata sheet. */
  if ((uint32_t)(*VREFINT_CAL_ADDR) != 0xFFFF) {
#endif
#ifdef __LL_ADC_CALC_VREFANALOG_VOLTAGE
#ifdef STM32U5xx
    Vref = __LL_ADC_CALC_VREFANALOG_VOLTAGE(ADC1, analogRead(AVREF), LL_ADC_RESOLUTION);
#else
    Vref = __LL_ADC_CALC_VREFANALOG_VOLTAGE(analogRead(AVREF), LL_ADC_RESOLUTION_12B);
#endif
#else
  Vref = VREFINT * ADC_RANGE / analogRead(AVREF);  // ADC sample to mV
#endif
#ifdef STM32U0xx
  }
#endif
  return Vref;
}
#endif

#ifdef ATEMP
static int32_t readTempSensor(int32_t VRef) {
  uint32_t temp = 0;
#ifdef __LL_ADC_CALC_TEMPERATURE
#ifdef STM32U5xx
  temp = __LL_ADC_CALC_TEMPERATURE(ADC1, VRef, analogRead(ATEMP), LL_ADC_RESOLUTION);
#elif defined(STM32WB0x) || defined(STM32WL3x)
  (void)VRef;
  temp = __LL_ADC_CALC_TEMPERATURE(analogRead(ATEMP), LL_ADC_DS_DATA_WIDTH_12_BIT);
#else
//__LL_ADC_CALC_TEMPERATURE
  temp = __LL_ADC_CALC_TEMPERATURE(VRef, analogRead(ATEMP), LL_ADC_RESOLUTION_12B);
#endif
#elif defined(__LL_ADC_CALC_TEMPERATURE_TYP_PARAMS)
  temp = __LL_ADC_CALC_TEMPERATURE_TYP_PARAMS(AVG_SLOPE, VTEMP, CALX_TEMP, VRef, analogRead(ATEMP), LL_ADC_RESOLUTION);
#endif
  return temp;
}
#endif

struct MCUData
{
    float temperature;
    float vref;
};
MCUData mcu_data;

void mcu_read() {
    mcu_data.vref = readVref();
    mcu_data.temperature = readTempSensor(mcu_data.vref);
}

#endif