

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 37

#define CIRCLEPIN 8

#define NUM_LEDS 30

#define CIRCLEPIN 8

#define NUM_LEDS_CIRCLE 12

#define BRIGHTNESS 10

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel circle = Adafruit_NeoPixel(NUM_LEDS_CIRCLE, CIRCLEPIN, NEO_GRBW + NEO_KHZ800);

bool mSSwitchState, mSSwitchStateLast; //monoStereoSwitch

elapsedMillis fps;
void audioSetup() {
  AudioMemory(12);
  strip.setBrightness(BRIGHTNESS);
  strip.begin();
  strip.show();
  circle.setBrightness(BRIGHTNESS);
  circle.begin();
  circle.show();
  mSSwitchState = digitalRead(monoStereoPin);
}
//this tests to see if the mono/stereo switch is on or off and returns if it has just been switched on
bool checkSwitch() {
  mSSwitchStateLast = mSSwitchState;
  mSSwitchState = digitalRead(monoStereoPin);
  if (mSSwitchState == HIGH) {
    return HIGH;
  }
  else  {
    return LOW;
  }
}

// this function makes the leds light up based on amplitude in stereo
void liveGainStereo () {
  if (fps > 24) {
    if (peak1.available() && peak2.available()) {
      fps = 0;
      int leftPeak = peak1.read() * 16.0;
      int rightPeak = peak2.read() * 16.0;

      Serial.println(leftPeak);
      Serial.println(rightPeak);
      Serial.println();
      for (int cnt = 0; cnt < 15; cnt++) {
        if (cnt < leftPeak - 1 || cnt < rightPeak - 1) {
          //this loop sets the top several LEDs to gradate from yellow to red if the signal is peaking
          if (cnt > 13 && leftPeak > 15) {
            //yellow
            strip.setPixelColor(6, 255, 195, 0, 0);
            strip.setPixelColor(7, 255, 170, 0, 0);
            strip.setPixelColor(8, 255, 146, 0, 0);
            //orange
            strip.setPixelColor(9, 255, 121, 0, 0);
            strip.setPixelColor(10, 255, 97,  0, 0);
            strip.setPixelColor(11, 255, 73,  0, 0);
            //red
            strip.setPixelColor(12, 255, 48,  0, 0);
            strip.setPixelColor(13, 255, 24,  0, 0);
            strip.setPixelColor(14, 255, 16,  0, 0);
            strip.show();
          }
          else {
            strip.setPixelColor(cnt, 30, 195, 18, 0);
            strip.show();
          }
          if (cnt > 13 && rightPeak > 15) {
            //yellow
            strip.setPixelColor(23, 255, 195, 0, 0);
            strip.setPixelColor(22, 255, 170, 0, 0);
            strip.setPixelColor(21, 255, 146, 0, 0);
            //orange
            strip.setPixelColor(20, 255, 121, 0, 0);
            strip.setPixelColor(19, 255, 97,  0, 0);
            strip.setPixelColor(18, 255, 73,  0, 0);
            //red
            strip.setPixelColor(17, 255, 48,  0, 0);
            strip.setPixelColor(16, 255, 24,  0, 0);
            strip.setPixelColor(15, 255, 16,  0, 0);
            strip.show();
          }
          else {
            strip.setPixelColor(29 - cnt, 30, 195, 18, 0);
            strip.show();
          }




        }
        else
        {
          strip.setPixelColor(cnt, 0, 0, 0, 0);
          strip.setPixelColor(29 - cnt, 0, 0, 0, 0);
          strip.show();
        }
      }

    }

  }

  delay(10);
}

//this does the same as above except with a mono signal, using all 30 LEDs 
void liveGainMono () {
  
  for (int x = 0; x <NUM_LEDS_CIRCLE; x++){
      circle.setPixelColor(x, 0, 0, 0, 255);
  }
  circle.show();
 // delay (10);
  if (fps > 24) {
    if (peak1.available()) {
      fps = 0;
      int monoPeak = peak1.read() * 31.0;
      Serial.println(monoPeak);
      for (int cnt = 0; cnt < 30; cnt++) {
        if (cnt < monoPeak - 1 ) {
          if (cnt > 28 && monoPeak > 30) {
            //yellow
            strip.setPixelColor(21, 255, 195, 0, 0);
            strip.setPixelColor(22, 255, 170, 0, 0);
            strip.setPixelColor(23, 255, 146, 0, 0);
            //orange
            strip.setPixelColor(24, 255, 121, 0, 0);
            strip.setPixelColor(25, 255, 97,  0, 0);
            strip.setPixelColor(26, 255, 73,  0, 0);
            //red
            strip.setPixelColor(27, 255, 48,  0, 0);
            strip.setPixelColor(28, 255, 24,  0, 0);
            strip.setPixelColor(29, 255, 16,  0, 0);
            strip.show();
          }
          else {
            strip.setPixelColor(cnt, 30, 195, 18, 0);
            strip.show();
          }

        }
        else
        {
          strip.setPixelColor(cnt, 0, 0, 0, 0);
          strip.show();
        }
      }
    }

    delay(10);
  }

}







/*
void pixelLoop() {

  for (i; i < NUM_LEDS; i++) {
    if (i % 4 == 0){
      circle.setPixelColor(i, 255, 128, 0, 0);
      circle.show();
      delay(75);
    }
    else if (i % 3 == 0) {
      circle.setPixelColor(i, 240, 25, 120, 0);
      circle.show();
      delay(75);
    }
    else if (i % 2 ==0){
      circle.setPixelColor(i, 153, 0, 153, 0);
      circle.show();
      delay(75);
    }
    else {
      circle.setPixelColor(i, 0, 0, 255, 0);
      circle.show();
      delay(75);
    }
  }
    i = i-NUM_LEDS+1;
}
*/
void whiteStrand(){
  for (int x = 0; x <NUM_LEDS; x++){
      circle.setPixelColor(x, x*15, x*10, (x+1)*5, 0);
      circle.show();
      delay (100);
  }
  
  
}

