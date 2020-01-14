#include "Button.h" 
#include "Flipper.h"

Button WhiteButton(D0, A2, "White");
Button GreenButton(D4, A1, "White");
Button RedButton(D5, A0, "White");
Button BlueButton(D3, A3, "White");
Button YellowButton(D2, A4, "White");

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
