#include "Button.h"

Button::Button(uint8_t buttonPin, uint8_t ledPin, String name, void (*callback)(String text)) : 
            ClickButton(buttonPin, LOW, CLICKBTN_PULLUP) {
    _cb = callback;
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
        Particle.publish("SINGLE click", PRIVATE);
  } 
  if(_clickcount == 2) _cb(_name + " doubleclick");
  if(_clickcount == 3) Particle.publish("TRIPLE click", PRIVATE);
  if(_clickcount == -1) {
        Particle.publish("SINGLE LONG click", PRIVATE);
  } 
  if(_clickcount == -2) Particle.publish("DOUBLE LONG click", PRIVATE);
  if(_clickcount == -3) Particle.publish("TRIPLE LONG click", PRIVATE);

  _clickcount = 0;
}

void Button::Switch() {
      _ledState = !_ledState;
      digitalWrite(_ledpin, _ledState);
}

//void Button::setcb(void (*callback)(String text)) {
//    _cb = &callback;
//}
