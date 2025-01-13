#include <DFRobot_SGP40.h>      // Include the SGP40 library
#include <Adafruit_NeoPixel.h>  // Include the NeoPixel library

// VOC sensor setup
DFRobot_SGP40 mySgp40;

// NeoPixel setup
#define pixelPin 6
#define NUMPIXELS 8
Adafruit_NeoPixel pixels(NUMPIXELS, pixelPin);  // Declare the NeoPixel object

void setup() {
  Serial.begin(115200);
  pixels.setBrightness(255);

  // Initialize the SGP40 sensor
  while (mySgp40.begin(/*duration = */10000) != true) {
    Serial.println("Failed to init chip, please check if the chip connection is fine");
    delay(1000);
  }
  Serial.println("sgp40 initialized successfully!");

  // Setup NeoPixel
  pixels.begin();  // Initialize the NeoPixel library
  pixels.clear();  // Turn off all LEDs
  pixels.show();   // Apply changes
}

void loop() {
  // Get a single VOC index reading
  uint16_t vocIndex = mySgp40.getVoclndex();

  // Print the VOC index to the Serial Monitor
  Serial.print("VOC Index = ");
  Serial.println(vocIndex);

  // Determine LED behavior based on the VOC index
  if (vocIndex < 100) {
    pixels.clear();  // Turn off LEDs if VOC is low
    pixels.show();
    return;  // Skip the rest of the loop and avoid further processing
  }

  // Choose color based on the VOC index
  int color;
  if (vocIndex <= 150) {
    color = pixels.Color(0, 255, 0);  // Green
  } else if (vocIndex <= 200) {
    color = pixels.Color(255, 165, 0);  // Orange
  } else {
    color = pixels.Color(255, 0, 0);  // Red
  }

  // Set the LEDs to the chosen color
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, color);  // Set each pixel to the selected color
  }
  pixels.show();

  // Delay before taking the next reading
  delay(1000);  // Delay 1 second before the next reading
}

