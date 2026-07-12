#ifndef _BNP_PWMOUTPUT_H
#define _BNP_PWMOUTPUT_H

#include "sys/_intsup.h"
#include <Arduino.h>

namespace bnp {
    class PWMOutput {
    public:
        PWMOutput(int pin) {
            this->pin = pin;
        }

        void begin() {
            pinMode(this->pin, OUTPUT);
        }

        void set(unsigned int frequency, unsigned int duration = 0) {
            tone(this->pin, frequency, duration);
        }

        void clear() {
            noTone(this->pin);
        }

    private:
        int pin;
        bool defaultState;
        bool state;
        bool inverted;
    };
};

#endif
