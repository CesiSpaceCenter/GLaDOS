#include "blackbox.h"
#include <log.h>

Adafruit_FlashTransport_SPI racer::blackbox::flashTransport(PIN_FLASH_CS, bnp::spi[FLASH_SPI]);
Adafruit_SPIFlash racer::blackbox::flash(&flashTransport);
FatVolume racer::blackbox::fatfs;
File32 racer::blackbox::file;

int racer::blackbox::get_last_index() {
    int lastIndex = -1;
    for (int i = 0; i < 1000; i++) {
        if (fatfs.exists(String(i))) {
            lastIndex = i;
        } else {
            return lastIndex;
        }
    }
}

void racer::blackbox::start() {
    if (file.isOpen()) {
        file.close();
        bnp::panic("trying to open file while one is already open");
    }
    int nextIndex = get_last_index() + 1;
    file = fatfs.open(String(nextIndex), FILE_WRITE);
    BNP_LOG("opened file {}", nextIndex);
}

void racer::blackbox::end() {
    if (!file.isOpen()) {
        bnp::panic("trying to close file while none is open");
    }
    file.close();
    BNP_LOG("closed file");
}

void racer::blackbox::print_file(int index) {
    Serial.print("---- file:"); Serial.print(index); Serial.println(" ----");
    File32 fileRead = fatfs.open(String(index), FILE_READ);
    while (fileRead.available()) {
        Serial.print((char)fileRead.read());
    }
    fileRead.close();
    Serial.println("\n--------");
}

void racer::blackbox::print_last() {
    print_file(get_last_index());
}

void racer::blackbox::print_all() {
    for (int i = 0; i < 1000; i++) {
        if (fatfs.exists(String(i))) {
            print_file(i);
        } else {
            break;
        }
    }
}

void racer::blackbox::init() {
    BNP_LOG("initializing flash");
    if (!flash.begin()) bnp::panic("failed to init flash");
    BNP_LOG("flash capacity: {}MB\t JEDEC ID: {:x}", flash.size()/(1024*1024), flash.getJEDECID());

    BNP_LOG("initializing fatfs");
    if (!fatfs.begin(&flash)) bnp::panic("failed to mount filesystem");

    // dummy file just to have an object created
    file = fatfs.open("xxx", FILE_READ);
    file.close();

    BNP_LOG("initialization done");
}

void racer::blackbox::task(void* arg) {
    UNUSED(arg);
    while (true) {
        start();
        bnp::sleep(20);
        for (int i = 0; i < 100; i++) {
            file.println(millis());
            bnp::sleep(20);
        }
        end();
        print_last();
        bnp::sleep(10000);
    }
}