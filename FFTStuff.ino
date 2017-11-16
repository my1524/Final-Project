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
  AudioMemory(4);
  strip.setBrightness(BRIGHTNESS);
  strip.begin();
  strip.show();
}

void ledsMeanVolume () {
  if (fps > 24) {
    if (peak1.available()) {
      fps = 0;
      int monoPeak = peak1.read() * 30.0;
      Serial.println(monoPeak);
      for (int cnt = 0; cnt < 30; cnt++) {
        //change this so that it can go higher than 30 but if it does the to led is red instead of green
        if (cnt < monoPeak) {
          //change this to a green color
          strip.setPixelColor(cnt, 30, 195, 18, 0);
          strip.show();
        }
        //        delay(75);
        else
        {
          strip.setPixelColor(cnt, 0, 0, 0, 0);
          strip.show();
        }
      }
      //i = i - NUM_LEDS + 1;
    }

    delay(10);
  }
}


//determine if audio is playing

bool audioChecker() {
  float val = peak1.read();
  Serial.println(val);
  delay(10);
  if (val > 0)
  {

    return true;
  }
  else return false;

}

//function to analyze audio with fft
void analyzeAudio() {

}
