#ifndef BUTTON_H
#define BUTTON_H

class Button {

private:

  int button;
  int lastButtonState;
  unsigned long lastPressTime;
  unsigned long debounceDelay;

public:

  bool pressed;

  Button(int b);
  bool isPressed();
};

#endif