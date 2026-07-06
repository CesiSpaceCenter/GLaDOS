#include "i2c.h"
#include "bnp.h"

void bnp::I2CManager::init() {
    Serial.print("i2c: enabled I2C buses: ");

    #if I2C1_ENABLE
    Serial.print("I2C1 ");
    this->operator[](1)->begin();
    #endif
    
    #if I2C2_ENABLE
    Serial.print("I2C2 ");
    this->operator[](2)->begin();
    #endif

    #if I2C3_ENABLE
    Serial.print("I2C3 ");
    this->operator[](3)->begin();
    #endif
    Serial.println("");
}

TwoWire* bnp::I2CManager::operator[](int index) {
    if (index < 1 || index > bnp::num_i2c_buses) {
        String error_msg = "I2C bus index out of range " + String(index);
        bnp::panic(error_msg.c_str());
        return nullptr;
    }
    TwoWire* instance = this->i2c_buses[index-1];
    if (instance == nullptr) {
        String error_msg = "tried to use invalid I2C bus " + String(index);
        bnp::panic(error_msg.c_str());
        return nullptr;
    }
    return instance;
}