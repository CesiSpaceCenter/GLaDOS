#ifndef _RACER_BLACKBOX_H
#define _RACER_BLACKBOX_H

#include <bnp.h>
#include <hal/board.h>
#include <STM32FreeRTOS.h>
#include <Adafruit_SPIFlash.h>
#include <SdFat_Adafruit_Fork.h>

Adafruit_FlashTransport_SPI flashTransport(PIN_FLASH_CS, bnp::spi[FLASH_SPI]);
Adafruit_SPIFlash flash(&flashTransport);
FatVolume fatfs;
File32 file;

int blackbox_get_last_index() {
    int lastIndex = -1;
    for (int i = 0; i < 1000; i++) {
        if (fatfs.exists(String(i))) {
            lastIndex = i;
        } else {
            return lastIndex;
        }
    }
}

void blackbox_start() {
    if (file.isOpen()) {
        file.close();
        bnp::panic("trying to open file while one is already open");
    }
    int nextIndex = blackbox_get_last_index() + 1;
    file = fatfs.open(String(nextIndex), FILE_WRITE);
    Serial.print("bbx: opened file "); Serial.println(nextIndex);
}

void blackbox_end() {
    if (!file.isOpen()) {
        bnp::panic("trying to close file while none is open");
    }
    file.close();
    Serial.println("bbx: file closed");
}

void blackbox_print_file(int index) {
    Serial.print("---- file:"); Serial.print(index); Serial.println(" ----");
    File32 fileRead = fatfs.open(String(index), FILE_READ);
    while (fileRead.available()) {
        Serial.print((char)fileRead.read());
    }
    fileRead.close();
    Serial.println("\n--------");
}

void blackbox_print_last() {
    blackbox_print_file(blackbox_get_last_index());
}

void blackbox_print_all() {
    for (int i = 0; i < 1000; i++) {
        if (fatfs.exists(String(i))) {
            blackbox_print_file(i);
        } else {
            break;
        }
    }
}

void blackbox_init() {
    Serial.println("bbx: init");
    if (!flash.begin()) bnp::panic("failed to init flash");
    Serial.print("bbx: flash capacity: "); Serial.print(flash.size()/(1024*1024)); Serial.println("MB");
    Serial.print("bbx: flash JEDECID: "); Serial.println(flash.getJEDECID(), HEX);

    Serial.println("bbx: init fatfs");
    if (!fatfs.begin(&flash)) bnp::panic("failed to mount filesystem");

    // dummy file just to have an object created
    file = fatfs.open("xxx", FILE_READ);
    file.close();
}

void blackbox_task(void* arg) {
    UNUSED(arg);
    while (true) {
        blackbox_start();
        vTaskDelay(((10000) * configTICK_RATE_HZ) / 1000L);  // 20Hz
        for (int i = 0; i < 100; i++) {
            file.println(millis());
            vTaskDelay(((30) * configTICK_RATE_HZ) / 1000L);  // 20Hz
        }
        blackbox_end();
        blackbox_print_last();
        vTaskDelay(((5000) * configTICK_RATE_HZ) / 1000L);  // 20Hz
    }
}

#endif