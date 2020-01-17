#include "Button.h" 
#include "Flipper.h"
#include "../lib/HttpClient/src/HttpClient.h"
#include <math.h> 

Button WhiteButton(D0, A2, "White", White);
Button GreenButton(D4, A1, "Green", Green);
Button RedButton(D5, A0, "Red", Red);
Button BlueButton(D3, A3, "Blue", Blue);
Button YellowButton(D2, A4, "Yellow", Yellow);

Flipper Flip(D1, Flipped);

const String _hueIp = "192.168.1.156";
const String _hueClient = "";
String _hueLamp = "7";

HttpClient http;

http_header_t headers[] = {
    { "Accept" , "*/*"},
    { NULL, NULL } // NOTE: Always terminate headers will NULL
};

http_request_t request;
http_response_t response;

void setup()
{
  Particle.publish("Push it", PRIVATE);
  Particle.function("SetLampId", SetLampId);
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
  Particle.publish(String("Alert: " + text), PRIVATE);
}

void Flipped(boolean high) {
  if (high) {
    LightOn();

  }
  else {
    LightOff();
  }
}

void Brightness(int val) {
    HueState("{\"bri\":" + String(val) + "}");
}

void LightOn() {
    HueState("{\"on\":true, \"bri\":254}");
}

void LightOff() {
    HueState("{\"on\":false}");
}

void Red(String name) {
  SetColor(255, 0, 0);
}

void Green(String name) {
  SetColor(0, 255, 0);
}

void Blue(String name) {
  SetColor(0, 0, 255);
}

void White(String name) {
  SetColor(255, 255, 255);
}

void Yellow(String name) {
  SetColor(255, 255, 0);
}

void HueState(String body) {
    request.hostname = _hueIp;
    request.port = 80;
    request.path = "/api/" + _hueClient + "/lights/" + _hueLamp + "/state";
    request.body = body;
    http.put(request, response);
}

// inspiration:
// https://gist.github.com/popcorn245/30afa0f98eea1c2fd34d
void SetColor(int r, int g, int b ) {
  float red = r / 255;
  float green = g / 255;
  float blue = b / 255;
  red = (red > 0.04045f) ? pow((red + 0.055f) / (1.0f + 0.055f), 2.4f) : (red / 12.92f);
  green = (green > 0.04045f) ? pow((green + 0.055f) / (1.0f + 0.055f), 2.4f) : (green / 12.92f);
  blue = (blue > 0.04045f) ? pow((blue + 0.055f) / (1.0f + 0.055f), 2.4f) : (blue / 12.92f);
  float X = red * 0.649926f + green * 0.103455f + blue * 0.197109f;
  float Y = red * 0.234327f + green * 0.743075f + blue * 0.022598f;
  float Z = red * 0.0000000f + green * 0.053077f + blue * 1.035763f;  
  float x = X / (X + Y + Z);
  float y = Y / (X + Y + Z);
  Particle.publish(String("x: " + String(x) + " y: " + String(y)), PRIVATE);
  HueState("{\"xy\":[" + String(x) + "," + String(y) +"]}"); 
}

int SetLampId(String lampId) {
  _hueLamp = lampId;
  return 0;
}