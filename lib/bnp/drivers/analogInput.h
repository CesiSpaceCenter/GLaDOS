#include <Arduino.h>

namespace bnp {
    class AnalogInput {
    public:
        AnalogInput(int pin) {
            this->pin = pin;
        }

        void begin() {
            pinMode(this->pin, INPUT);
            analogReadResolution(16);
        }

        uint32_t get() {
            return analogRead(this->pin);
        }

    private:
        int pin;
    };
};