#include "Particle.h"

class Flipper {
    public:
        Flipper(uint8_t pin) {
            _pin = pin;
            pinMode(_pin, INPUT_PULLDOWN);
        };
        boolean Read() {
            boolean newstate = digitalRead(_pin);
            if (newstate != _state) {
                Particle.publish("Flip!");
                _state = newstate;
            }
            return _state;
        };
    private:
        uint8_t _pin;
        boolean _state;
};