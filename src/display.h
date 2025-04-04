#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_SSD1306.h>

// Ustawienia wyświetlacza OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1  // Brak pinu resetującego

// Inicjalizacja wyświetlacza
extern Adafruit_SSD1306 display;

// Deklaracje funkcji
bool initDisplay();
void updateDisplay(float bmpTemperature, float bmpPressure, float ahtTemperature, float ahtHumidity);
void displayMessage(const char* message);

#endif // DISPLAY_H
