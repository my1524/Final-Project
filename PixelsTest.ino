#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 6

#define NUM_LEDS 30

#define BRIGHTNESS 10

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);
int i = 0;

void pixelSetup() {
  strip.setBrightness(BRIGHTNESS);
  strip.begin();
  strip.show();
}

void pixelLoop() {

  for (i; i < NUM_LEDS; i++) {
    if (i % 4 == 0){
      strip.setPixelColor(i, 255, 128, 0, 0);
      strip.show();
      delay(75);
    }
    else if (i % 3 == 0) {
      strip.setPixelColor(i, 240, 25, 120, 0);
      strip.show();
      delay(75);
    }
    else if (i % 2 ==0){
      strip.setPixelColor(i, 153, 0, 153, 0);
      strip.show();
      delay(75);
    }
    else {
      strip.setPixelColor(i, 0, 0, 255, 0);
      strip.show();
      delay(75);
    }
  }
    i = i-NUM_LEDS+1;
}

void whiteStrand(){
  for (int x = 0; x <NUM_LEDS; x++){
      strip.setPixelColor(x, 0, 0, 0, 255);
  }
  strip.show();
  delay (1000);
}

