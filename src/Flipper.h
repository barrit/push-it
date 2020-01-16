#include "Particle.h"

class Flipper {
    public:
        Flipper(uint8_t pin, void (*callback)(boolean up)) {
            _pin = pin;
            pinMode(_pin, INPUT_PULLDOWN);
            _callback = callback;
        };
        boolean Read() {
            boolean newstate = digitalRead(_pin);
            if (newstate != _state) {
                _callback(newstate);
                _state = newstate;
            }
            return _state;
        };
    private:
        uint8_t _pin;
        boolean _state;
        void (*_callback) (boolean up);
};