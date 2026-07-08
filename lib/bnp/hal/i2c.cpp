#include "i2c.h"
#include "bnp.h"
#include "log.h"
#include <fmt.h>

void bnp::I2CManager::init() {
    #if I2C1_ENABLE
    this->operator[](1)->begin();
    #endif

    #if I2C2_ENABLE
    this->operator[](2)->begin();
    #endif

    #if I2C3_ENABLE
    this->operator[](3)->begin();
    #endif

    BNP_LOG(
        "enabled I2C buses: {}{}{}",
        (I2C1_ENABLE ? "I2C1 ": ""), (I2C2_ENABLE ? "I2C2 ": ""), (I2C3_ENABLE ? "I2C3 ": "")
    );
}

TwoWire* bnp::I2CManager::operator[](int index) {
    if (index < 1 || index > bnp::num_i2c_buses) {
        bnp::panic(fmt::format("I2C bus index out of range {}", index));
        return nullptr;
    }
    TwoWire* instance = this->i2c_buses[index-1];
    if (instance == nullptr) {
        bnp::panic(fmt::format("tried to use invalid I2C bus {}", index));
        return nullptr;
    }
    return instance;
}
