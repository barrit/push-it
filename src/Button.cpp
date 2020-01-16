#include "Button.h"

Button::Button(uint8_t buttonPin, uint8_t ledPin, String name, void (*callback)(String text)) : 
            ClickButton(buttonPin, LOW, CLICKBTN_PULLUP) {
    _callback = callback;
    _ledpin = ledPin;
    _name = name;
    _clickcount = 0;
    _ledState = LOW;
    //The button
    pinMode(buttonPin, INPUT_PULLUP);
    //The led
    pinMode(ledPin, OUTPUT);
}

void Button::Update() {

   ClickButton::Update();

  if(clicks != 0) _clickcount = clicks;

  if(_clickcount == 1) {
        Switch();
        _callback(_name);
  } 
  if(_clickcount == 2) Particle.publish("DOUBLE click", PRIVATE);
  if(_clickcount == -1) {
        Particle.publish("SINGLE LONG click", PRIVATE);
  } 
  _clickcount = 0;
}

void Button::Switch() {
      _ledState = !_ledState;
      digitalWrite(_ledpin, _ledState);
}

//void Button::setcb(void (*callback)(String text)) {
//    _cb = &callback;
//}
