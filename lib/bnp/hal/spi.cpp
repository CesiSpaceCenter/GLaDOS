#include "spi.h"
#include "bnp.h"
#include "log.h"
#include <fmt.h>

void bnp::SPIManager::init() {
    #if SPI1_ENABLE
    this->operator[](1)->setMISO(PIN_SPI1_MISO);
    this->operator[](1)->setMOSI(PIN_SPI1_MOSI);
    this->operator[](1)->setSCLK(PIN_SPI1_SCK);
    this->operator[](1)->begin();
    #endif

    #if SPI2_ENABLE
    this->operator[](2)->begin();
    #endif

    #if SPI3_ENABLE
    this->operator[](3)->begin();
    #endif

    BNP_LOG(
        "enabled SPI buses: {}{}{}",
        (SPI1_ENABLE ? "SPI1 ": ""), (SPI2_ENABLE ? "SPI2 ": ""), (SPI3_ENABLE ? "SPI3 ": "")
    );
}

SPIClass* bnp::SPIManager::operator[](int index) {
    if (index < 1 || index > bnp::num_spi_buses) {
        bnp::panic(fmt::format("SPI bus index out of range {}", index));
        return nullptr;
    }
    SPIClass* instance = this->spi_buses[index-1];
    if (instance == nullptr) {
        bnp::panic(fmt::format("tried to use invalid SPI bus {}", index));
        return nullptr;
    }
    return instance;
}
