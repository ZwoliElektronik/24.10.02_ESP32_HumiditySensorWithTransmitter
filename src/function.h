// function.h

#ifndef FUNCTION_H
#define FUNCTION_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>


// External declaration of the NeoPixel strip object
extern Adafruit_NeoPixel strip;

// Fan control pin
#define FAN_PIN 5
#define BUTTON_PIN 4  // Jeśli przycisk jest na GPIO 4

// Global variables for fan control
extern bool fanShouldBeOn;  // Flaga sterująca stanem wentylatora

// Function prototypes
void fanControl(float humidity);
void buttonControl();
void updateFanState();  // Nowa funkcja do jednolitego sterowania wentylatorem

extern bool manualFanOverride;
extern bool fanShouldBeOn;



#endif
