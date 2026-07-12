#ifndef _BNP_PWMINPUT_H
#define _BNP_PWMINPUT_H

#include <Arduino.h>
#include <cstdint>

namespace bnp {
    class PWMInput {
    public:
        PWMInput(int pin, int mode = INPUT) {
            this->pin = pin;
            this->mode = mode;
        }

        void begin() {
            pinMode(this->pin, this->mode);
        }

        int read(uint32_t timeout = 1000000L, bool state = HIGH) {
            return pulseIn(this->pin, state);
        }

    private:
        int pin;
        int mode;
    };
};

#endif
