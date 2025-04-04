#include "sensors.h"

// Funkcja inicjalizująca czujniki
bool initSensors(Adafruit_BMP280 *bmp, Adafruit_AHTX0 *aht) {
  if (!bmp->begin(0x76) && !bmp->begin(0x77)) {
    Serial.println(F("Nie można znaleźć czujnika BMP280!"));
    return false;
  }

  if (!aht->begin()) {
    Serial.println("Nie można znaleźć czujnika AHT20!");
    return false;
  }

  Serial.println(F("Czujniki zainicjowane."));
  return true;
}

// Funkcja odczytująca dane z czujników
bool readSensors(Adafruit_BMP280 *bmp, Adafruit_AHTX0 *aht, float *bmpTemperature, float *bmpPressure, float *ahtHumidity, float *ahtTemperature) {
  *bmpTemperature = bmp->readTemperature();
  *bmpPressure = bmp->readPressure() / 100.0F;

  sensors_event_t humidity, temperature;
  aht->getEvent(&temperature, &humidity);
  
  // Upewnij się, że temperatura i wilgotność są poprawnie przypisane
  *ahtTemperature = temperature.temperature; // Temperatura z AHT20
  *ahtHumidity = humidity.relative_humidity; // Wilgotność z AHT20

  return true;
}
