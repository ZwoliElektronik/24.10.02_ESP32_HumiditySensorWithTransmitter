#include <Wire.h>
#include "display.h"

// Inicjalizacja wyświetlacza
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

bool initDisplay() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Błąd inicjalizacji SSD1306!"));
    return false;  // Zwracamy false w przypadku błędu
  }
  display.clearDisplay();
  display.display();
  return true;  // Zwracamy true, jeśli inicjalizacja się powiodła
}

void updateDisplay(float bmpTemperature, float bmpPressure, float ahtTemperature, float ahtHumidity) {
  display.clearDisplay();
  display.setTextSize(1);  // Rozmiar tekstu 1 (6 pikseli szerokości na znak)
  display.setTextColor(WHITE);
  
  // Linia 1: Nazwa czujnika BMP280
  String bmpLabel = "| BMP280 |";
  int16_t x = (128 - (bmpLabel.length() * 6)) / 2;  // Wyśrodkowanie tekstu na szerokości 128 pikseli
  display.setCursor(0, 0);  // Y = 0 (pierwsza linia)
  display.print(bmpLabel);
  
  // Linia 2: Temperatura BMP280
  String bmpTemp = "Temp: " + String(bmpTemperature, 1) + " 'C";
  x = (128 - (bmpTemp.length() * 6)) / 2;  // Wyśrodkowanie tekstu
  display.setCursor(x, 10);  // Y = 10 (druga linia, z odstępem)
  display.print(bmpTemp);
  
  // Linia 3: Ciśnienie BMP280
  String bmpPress = "Pressure: " + String(bmpPressure, 1) + " hPa";
  x = (128 - (bmpPress.length() * 6)) / 2;  // Wyśrodkowanie tekstu
  display.setCursor(x, 20);  // Y = 20 (trzecia linia)
  display.print(bmpPress);
  
  // Linia 4: Nazwa czujnika AHT20
  String ahtLabel = "| AHT20 |";
  x = (128 - (ahtLabel.length() * 6)) / 2;  // Wyśrodkowanie tekstu
  display.setCursor(0, 35);  // Y = 35 (czwarta linia)
  display.print(ahtLabel);
  
  // Linia 5: Temperatura AHT20
  String ahtTemp = "Temp: " + String(ahtTemperature, 1) + " 'C";
  x = (128 - (ahtTemp.length() * 6)) / 2;  // Wyśrodkowanie tekstu
  display.setCursor(x, 45);  // Y = 45 (piąta linia)
  display.print(ahtTemp);
  
  // Linia 6: Wilgotność AHT20
  String ahtHum = "Humidity: " + String(ahtHumidity, 1) + " %";
  x = (128 - (ahtHum.length() * 6)) / 2;  // Wyśrodkowanie tekstu
  display.setCursor(x, 55);  // Y = 55 (szósta linia)
  display.print(ahtHum);

  display.display();  // Wyświetlenie zaktualizowanych danych
}


void displayMessage(const char* message) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  
  // Wysrodkowanie tekstu
  String msgString = message;
  display.setCursor((SCREEN_WIDTH - msgString.length() * 6) / 2, (SCREEN_HEIGHT - 8) / 2); // 8 to wysokość tekstu w rozmiarze 1
  display.println(msgString);
  display.display();
}
