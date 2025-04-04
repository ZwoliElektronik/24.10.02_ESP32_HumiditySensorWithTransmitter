// function.cpp

#include "function.h"

// Global flag for fan state
bool fanShouldBeOn = false;
bool manualFanOverride = false;

// Global threshold for humidity
const float humidityThreshold = 60.0; 

// Function to control the fan based on humidity
void fanControl(float humidity) {
  if (!manualFanOverride) {  // Tylko jeśli przycisk NIE wymusił działania
    if (humidity >= humidityThreshold) {
      fanShouldBeOn = true;
      strip.setPixelColor(0, strip.Color(50, 0, 15)); // Ustawienie  koloru
      strip.show(); // Aktualizacja diody
    } else {
      fanShouldBeOn = false;
      strip.setPixelColor(0, strip.Color(0, 50, 15)); // Ustawienie  koloru
      strip.show(); // Aktualizacja diody
    }
  }
}


// Function to handle button press logic
void buttonControl() {
  static unsigned long lastPressTime = 0;
  static bool buttonPressedLast = false;
  static unsigned long fanTurnOffTime = 0;
  const unsigned long debounceDelay = 200; // 200 ms
  const unsigned long fanOnDuration = 600000; // 10 minut

  bool buttonPressed = digitalRead(BUTTON_PIN) == LOW;

  if (buttonPressed && !buttonPressedLast && millis() - lastPressTime > debounceDelay) {
    fanShouldBeOn = true;
    manualFanOverride = true;  // Ręczna kontrola priorytetowa
    fanTurnOffTime = millis() + fanOnDuration;

    strip.setPixelColor(0, strip.Color(0, 50, 0)); // Czerwony LED
    strip.show();
    lastPressTime = millis();
  }

  if (manualFanOverride && millis() > fanTurnOffTime) {
    manualFanOverride = false;  // Koniec priorytetowego sterowania
  }

  buttonPressedLast = buttonPressed;
}


// Function to update the fan state based on the flag
void updateFanState() {
  if (fanShouldBeOn) {
    digitalWrite(FAN_PIN, HIGH);
    strip.setPixelColor(0, strip.Color(0, 50, 0)); // Czerwony LED
  } else {
    digitalWrite(FAN_PIN, LOW);
    strip.setPixelColor(0, strip.Color(0, 50, 15)); // Zielony LED
  }
  strip.show();
}

