#include "../lib/clickButton/src/clickButton.h"

class Button : public ClickButton
{
  public:
    Button(uint8_t buttonPin, uint8_t ledPin, String name);
    void Update();
    void Switch();
private:
    uint8_t _ledpin;
    String _name;
    int _clickcount;    
    boolean _ledState;
};

