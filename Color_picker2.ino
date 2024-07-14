#include <Wire.h>
#include <Adafruit_TCS34725.h>

// Pins for RGB LED
#define redPin 5
#define greenPin 6
#define bluePin 3

// Pin for push button
#define buttonPin 2


// Color sensor setup
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

// Variables to store RGB values
uint16_t redValue, greenValue, blueValue;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Initialize RGB LED pins
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // Initialize button pin
  pinMode(buttonPin, INPUT_PULLUP);


  // Initialize color sensor
  if (!tcs.begin()) {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); // Halt if the sensor is not found
  }

  Serial.println("TCS34725 is detected");
}

void loop() {
  // Check if the button is pressed
  if (digitalRead(buttonPin) == HIGH) {
    delay(100); // Debounce delay

    // Read color
    readColor();

    // Display color on RGB LED
    setColor(redValue, greenValue, blueValue);

    
    
  }
}

void readColor() {
  uint16_t clear;
  
  // Read the color sensor
  tcs.getRawData(&redValue, &greenValue, &blueValue, &clear);

  Serial.print(" R: "); Serial.print(redValue); 
  Serial.print(" G: "); Serial.print(greenValue); 
  Serial.print(" B: "); Serial.println(blueValue);
}

void setColor(uint16_t red, uint16_t green, uint16_t blue) {
  analogWrite(redPin, map(red, 0, 65535, 0, 255));
  analogWrite(greenPin, map(green, 0, 65535, 0, 255));
  analogWrite(bluePin, map(blue, 0, 65535, 0, 255));
}


bool isColor(uint16_t r, uint16_t g, uint16_t b, uint16_t targetR, uint16_t targetG, uint16_t targetB) {
  int tolerance = 20;
  return (abs(r - targetR) < tolerance && abs(g - targetG) < tolerance && abs(b - targetB) < tolerance);
}
