#ifndef _BNP_DIGITALINPUT_H
#define _BNP_DIGITALINPUT_H

#include <Arduino.h>

namespace bnp {
    class DigitalInput {
    public:
        DigitalInput(int pin, bool inverted = false, int mode = INPUT) {
            this->pin = pin;
            this->inverted = inverted;
            this->mode = mode;
        }

        void begin() {
            pinMode(this->pin, this->mode);
        }

        bool state() {
            bool state = digitalRead(this->pin);
            if (this->inverted) state = !state;
            return state;
        }

        bool is_on() {
            return this->state();
        }

        bool is_off() {
            return !this->state();
        }

    private:
        int pin;
        int mode;
        bool inverted;
    };
};

#endif
