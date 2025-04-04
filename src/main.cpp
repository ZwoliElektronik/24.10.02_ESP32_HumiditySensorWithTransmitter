// main.cpp

/*

YourProject/
├── src/
│   ├── main.cpp
│   ├── sensors.h
│   ├── sensors.cpp
│   ├── function.h
│   ├── function.cpp
│   ├── display.h
│   ├── display.cpp
│   └── calibrate.h

*/

#include <Wire.h>
#include "function.h"
#include "sensors.h"
#include "display.h"
#include "Calibrate.h"
#include <Adafruit_NeoPixel.h> // Sygnalizacja dla ESP32-C3

// Inicjalizacja czujników
Adafruit_BMP280 bmp; 
Adafruit_AHTX0 aht;

// Inicjalizacja Diody GRB IC
Adafruit_NeoPixel strip(1, 10, NEO_GRB + NEO_KHZ800);

// Pins setup
#define BUTTON_PIN 4
#define FAN_PIN 5

void setup() {
  Serial.begin(115200);
  Wire.begin(7, 6); // SDA = GPIO7, SCL = GPIO6 dla ESP32-C3

  pinMode(BUTTON_PIN, INPUT_PULLUP);  
  pinMode(FAN_PIN, OUTPUT);           

  strip.begin();
  strip.setPixelColor(0, strip.Color(40, 0, 25));
  strip.show();
  delay(1000);
  
  // Inicjalizacja wyświetlacza
  initDisplay();

  // Inicjalizacja czujników
  if (!initSensors(&bmp, &aht)) {
    displayMessage("Sensor init. failed");
    while (1); // Zatrzymaj, jeśli inicjalizacja czujników się nie uda
  }
  
  strip.setPixelColor(0, strip.Color(0, 50, 15));
  strip.show();
}

void loop() {

  float bmpTemperature, bmpPressure;
  float ahtTemperature, ahtHumidity;

  if (readSensors(&bmp, &aht, &bmpTemperature, &bmpPressure, &ahtTemperature, &ahtHumidity)) {
    bmpTemperature += BMP_TEMPERATURE_OFFSET;
    bmpPressure += BMP_PRESSURE_OFFSET;
    ahtHumidity += AHT_HUMIDITY_OFFSET;

    updateDisplay(bmpTemperature, bmpPressure, ahtTemperature, ahtHumidity);
  }

    buttonControl();
    fanControl(ahtHumidity);
    updateFanState();
  

  delay(1000);
}

