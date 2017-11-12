#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>


// GUItool: begin automatically generated code
AudioInputAnalog         adc1;           //xy=164,95
AudioAnalyzePeak         peak1;          //xy=317,123
AudioConnection          patchCord1(adc1, peak1);
// GUItool: end automatically generated code

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 6

#define NUM_LEDS 30

#define BRIGHTNESS 10

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);

elapsedMillis fps;
void pixelSetup() {
  strip.setBrightness(BRIGHTNESS);
  strip.begin();
  strip.show();
}

void ledsMeanVolume () {
  if (fps > 24) {
    if (peak1.available()) {
      fps = 0;
      int monoPeak = peak1.read() * 30.0;
      for (int cnt = 0; cnt < monoPeak; cnt++) {
        strip.setPixelColor(cnt, 240, 50, 240, 0);
        strip.show();
        delay(75);

      }
      //i = i - NUM_LEDS + 1;
    }

    delay(10);
  }
}


//determine if audio is playing
bool audioChecker() {
  if (peak1.read() > 0)
  {
    return true;
  }
  else return false;

}

//function to analyze audio with fft
void analyzeAudio() {

}
