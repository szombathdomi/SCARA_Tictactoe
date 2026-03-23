#include <Arduino.h>
#include "ButtonHandler.h"

const int HOME_BUTTON = 53;
const int SELECT_BUTTON = 51;
const int OK_BUTTON = 49;
const int START_BUTTON = 47;

void initButtons() {
  pinMode(HOME_BUTTON, INPUT_PULLUP);
  pinMode(START_BUTTON, INPUT_PULLUP);
  pinMode(OK_BUTTON, INPUT_PULLUP);
  pinMode(SELECT_BUTTON, INPUT_PULLUP);
}

bool isButtonPressed(int pin) {
  static const int pins[] = { HOME_BUTTON, START_BUTTON, OK_BUTTON, SELECT_BUTTON };
  static unsigned long lastT[4] = { 0 };
  static bool pressed[4] = { false };

  for (int i = 0; i < 4; i++) {
    if (pin == pins[i]) {
      if (digitalRead(pin) == LOW) {
        if (!pressed[i] && (millis() - lastT[i] > 50)) {
          lastT[i] = millis();
          return pressed[i] = true;
        }
      } else {
        pressed[i] = false;
      }
    }
  }
  return false;
}

bool isHomingPressed() {
  return isButtonPressed(HOME_BUTTON);
}

bool isStartPressed() {
  return isButtonPressed(START_BUTTON);
}

bool isOkPressed() {
  return isButtonPressed(OK_BUTTON);
}

bool isSelectPressed() {
  return isButtonPressed(SELECT_BUTTON);
}