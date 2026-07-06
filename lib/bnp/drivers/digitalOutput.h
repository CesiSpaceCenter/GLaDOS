#ifndef _BNP_DIGITALOUTPUT_H
#define _BNP_DIGITALOUTPUT_H

#include <Arduino.h>

namespace bnp {
    class DigitalOutput {
    public:
        DigitalOutput(int pin, bool defaultState = LOW, bool inverted = false) {
            this->pin = pin;
            this->defaultState = defaultState;
            this->state = defaultState;
            this->inverted = inverted;
        }

        void begin() {
            pinMode(this->pin, OUTPUT);
            this->set(this->defaultState);
        }

        void set(bool state) {
            this->state = state;
            if (this->inverted) {
                digitalWrite(this->pin, !state);
            } else {
                digitalWrite(this->pin, state);
            }
        }

        void on() {
            this->set(HIGH);
        }

        void off() {
            this->set(LOW);
        }

        void toggle() {
            this->set(!this->state);
        }

    private:
        int pin;
        bool defaultState;
        bool state;
        bool inverted;
    };
};

#endif
