#include <Arduino.h>
#include "Button.h"

Button::Button(int b) {
  button = b;
  pressed = false;
  lastButtonState = HIGH;
  lastPressTime = 0;
  debounceDelay = 50;

  pinMode(button, INPUT_PULLUP);
}

bool Button::isPressed() {
  
  int currentButtonState = digitalRead(button);

  if (currentButtonState == LOW && lastButtonState == HIGH && (millis() - lastPressTime) > debounceDelay) {
    pressed = !pressed;
    lastPressTime = millis();
  }

  lastButtonState = currentButtonState;

  return pressed;
}