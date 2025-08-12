#ifndef BUTTON_H
#define BUTTON_H

class Button {

private:

  int button;
  int lastButtonState;
  bool pressed;
  unsigned long lastPressTime;
  unsigned long debounceDelay;

public:

  Button(int b);
  bool isPressed();
};

#endif