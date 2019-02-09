#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputAnalogStereo   adcs1;          //xy=139,191
AudioAnalyzePeak         peak2;          //xy=284,289
AudioAnalyzePeak         peak1;          //xy=307,241
AudioAnalyzeFFT256       fft1;       //xy=373,164
AudioAnalyzeFFT256       fft2;       //xy=407,206
AudioConnection          patchCord1(adcs1, 0, peak1, 0);
AudioConnection          patchCord2(adcs1, 0, fft1, 0);
AudioConnection          patchCord3(adcs1, 1, peak2, 0);
AudioConnection          patchCord4(adcs1, 1, fft2, 0);
// GUItool: end automatically generated code


#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 37

#define NUM_LEDS 30

#define BRIGHTNESS 10

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);

bool mSSwitchState, mSSwitchStateLast; //monoStereoSwitch

elapsedMillis fps;
void audioSetup() {
  AudioMemory(12);
  strip.setBrightness(BRIGHTNESS);
  strip.begin();
  strip.show();
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




//the following functions aren't being used
//determine if audio is playing

bool audioChecker() {
  float val = peak1.read();
  // Serial.println(val);
  delay(10);
  if (val > 0)
  {

    return true;
  }
  else return false;

}
float binArray[30][4];

//function to analyze audio with fft
void analyzeAudio() {
  float n;
  int i;

  if (fft1.available()) {
    // each time new FFT data is available
    // print it all to the Arduino Serial Monitor
    for (int k = 0; k < 30; k++) {
      for (int l = 0; l < 4; l++) {
        binArray[k][l] = fft1.read(i);
        i++;
      }
    }
  }
}


void binAnalysis() {
  for (int k = 0; k < 30; k++) {
    Serial.print("{");
    for (int l = 0; l < 4; l++) {
      Serial.print(binArray[k][l]);
      Serial.print(", ");
    }
    Serial.println("}");
  }
  Serial.println(" ");
  Serial.println(" ");
}




