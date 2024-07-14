#include <Wire.h>
#include "Adafruit_TCS34725.h"

// Create a TCS34725 object
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

// Pin definitions for RGB LED
const int redPin = 5;
const int greenPin = 6;
const int bluePin = 3;

void setup() {
  Serial.begin(9600);

  // Initialize TCS34725
  if (tcs.begin()) {
    Serial.println("TCS34725 initialized");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }

  // Set up RGB LED pins
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  uint16_t r, g, b, c;

  // Read color values
  tcs.getRawData(&r, &g, &b, &c);
  Serial.print("Red: "); Serial.print(r);
  Serial.print(" Green: "); Serial.print(g);
  Serial.print(" Blue: "); Serial.print(b);
  Serial.println();

  // Normalize color values
  float total = r + g + b;
  if (total > 0) {
    float redRatio = r / total;
    float greenRatio = g / total;
    float blueRatio = b / total;

    // Set LED color based on the detected color
    setColor(redRatio * 255, greenRatio * 255, blueRatio * 255);
  }

  delay(500);
}

// Function to set color on RGB LED
void setColor(int red, int green, int blue) {
  analogWrite(redPin, 255 - red);   // Invert for common cathode
  analogWrite(greenPin, 255 - green); // Invert for common cathode
  analogWrite(bluePin, 255 - blue);   // Invert for common cathode
}
