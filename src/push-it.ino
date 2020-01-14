#include "Button.h" 
#include "Flipper.h"

Button WhiteButton(D0, A2, "White", Alert);
Button GreenButton(D4, A1, "Green", Alert);
Button RedButton(D5, A0, "Red", Alert);
Button BlueButton(D3, A3, "Blue", Alert);
Button YellowButton(D2, A4, "Yellow", Alert);

Flipper Flip(D1);


void setup()
{
  Particle.publish("Push it", PRIVATE);
}

void loop()
{
  if (Flip.Read() == HIGH)
  {
    WhiteButton.Update();
    GreenButton.Update();
    RedButton.Update();
    BlueButton.Update();
    YellowButton.Update();
  }
}

void Alert(String text) {
  Particle.publish("Alert: " + text);
}