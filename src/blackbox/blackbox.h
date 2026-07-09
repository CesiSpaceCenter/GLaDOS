#ifndef _RACER_BLACKBOX_H
#define _RACER_BLACKBOX_H


#include <bnp.h>
#include <STM32FreeRTOS.h>
#include <Adafruit_SPIFlash.h>
#include <SdFat_Adafruit_Fork.h>

namespace racer::blackbox {
    extern Adafruit_FlashTransport_SPI flashTransport;
    extern Adafruit_SPIFlash flash;
    extern FatVolume fatfs;
    extern File32 file;

    int get_last_index();
    void start();
    void end();
    void print_file(int index);
    void print_last();
    void print_all();
    void init();
    void task(void* arg);
}

#endif
