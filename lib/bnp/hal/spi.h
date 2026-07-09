#ifndef BNP_SPI_H
#define BNP_SPI_H

#include <SPI.h>

namespace bnp {
    const int num_spi_buses = 3;
    class SPIManager {
    public:
        void init();
        SPIClass* operator[](int index);

    private:
        SPIClass* spi_buses[3] = {
            #if SPI1_ENABLE
            &SPI,
            #else
            nullptr,
            #endif

            #if SPI2_ENABLE
            new SPIClass(PIN_SPI2_MOSI, PIN_SPI2_MISO, PIN_SPI2_SCK),
            #else
            nullptr,
            #endif

            #if SPI3_ENABLE
            new SPIClass(PIN_SPI3_MOSI, PIN_SPI3_MISO, PIN_SPI3_SCK),
            #else
            nullptr,
            #endif
        };
    };
};

#endif
