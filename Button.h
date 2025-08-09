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

  Button(int b) {
    button = b;
    pressed = false;
    lastButtonState = HIGH;
    lastPressTime = 0;
    debounceDelay = 50;

    pinMode(button, INPUT_PULLUP);
  }

  bool isPressed() {

    int currentButtonState = digitalRead(button);

    if (currentButtonState == LOW && lastButtonState == HIGH && (millis() - lastPressTime) > debounceDelay) {
      pressed = !pressed;
      lastPressTime = millis();
    }

    lastButtonState = currentButtonState;

    return pressed;
  }
};

#endif