#ifndef SENSORS_H
#define SENSORS_H

#include <Adafruit_BMP280.h>
#include <Adafruit_AHTX0.h>

// Deklaracje funkcji
bool initSensors(Adafruit_BMP280 *bmp, Adafruit_AHTX0 *aht);
bool readSensors(Adafruit_BMP280 *bmp, Adafruit_AHTX0 *aht, float *bmpTemperature, float *bmpPressure, float *ahtTemperature, float *ahtHumidity);

#endif // SENSORS_H
