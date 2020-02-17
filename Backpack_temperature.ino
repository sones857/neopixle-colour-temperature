#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>

#define PIN       2
#define NUMPIXELS 3
//#define BRIGHTNESS 2

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRBW + NEO_KHZ800);
Adafruit_BMP280 bmp; // I2C

// ################################################################

void setup()
{
      Serial.begin(9600);
      Serial.println(F("BMP280 test"));
      pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
      bmp.begin();

      bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                      Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                      Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                      Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                      Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}

// ################################################################

void changeColour(int colour)
{
      Serial.println(colour);
      pixels.clear(); // Set all pixel colors to 'off'
      for (int i = 0; i < NUMPIXELS; i++)
      {
            if (colour == 1) pixels.setPixelColor(i, pixels.Color(0, 0, 0, 50)); //white
            if (colour == 2) pixels.setPixelColor(i, pixels.Color(0, 0, 50, 0)); //blue
            if (colour == 3) pixels.setPixelColor(i, pixels.Color(0, 50, 50, 0)); //cyan
            if (colour == 4) pixels.setPixelColor(i, pixels.Color(0, 50, 0, 0)); //green
            if (colour == 5) pixels.setPixelColor(i, pixels.Color(50, 50, 0, 0)); //yellow
            if (colour == 6) pixels.setPixelColor(i, pixels.Color(50, 30, 0, 0)); //orange
            if (colour == 7) pixels.setPixelColor(i, pixels.Color(50, 0, 0, 0)); //red
            pixels.show();
      }
      delay(1000);
}

// ################################################################

void loop()
{
      float temperature = bmp.readTemperature();
      Serial.println(bmp.readTemperature());
      int colour;

      if (temperature < 0) colour = 1; // white
      else if (temperature >= 0 && temperature <= 5) colour = 2;  // blue
      else if (temperature >= 5 && temperature <= 10) colour = 3;  // cyan
      else if (temperature > 10 && temperature <= 15) colour = 4; // green
      else if (temperature >= 15 && temperature <= 20) colour = 5;  // yellow
      else if (temperature >= 20 && temperature <= 25) colour = 6;  // orange
      else if (temperature > 30) colour = 7; // red

      changeColour(colour);
}
