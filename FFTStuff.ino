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

elapsedMillis fps;
void audioSetup() {
  AudioMemory(12);
  strip.setBrightness(BRIGHTNESS);
  strip.begin();
  strip.show();
  //I think this is necessary for testing the frequency
}

// this function makes the leds light up based on amplitude
void liveGainStereo () {
  if (fps > 24) {
    if (peak1.available() && peak2.available()) {
      fps = 0;
      int stereoPeak1 = peak1.read() * 16.0;
      int stereoPeak2 = peak2.read() * 16.0;

      Serial.println(stereoPeak1);
      Serial.println(stereoPeak2);
      Serial.println();
      for (int cnt = 0; cnt < 15; cnt++) {
        if (cnt < stereoPeak1 - 1 || cnt < stereoPeak2 - 1) {
          if ((cnt > 14 && stereoPeak1 > 15) || (cnt > 14 && stereoPeak2 > 15)) {
            if (cnt > 14 && stereoPeak1 > 15) {
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

          }

          //        delay(75);
          if (cnt < stereoPeak2 - 1 ) {
            if (cnt > 14 && stereoPeak2 > 15) {
              //yellow
              strip.setPixelColor(15, 255, 195, 0, 0);
              strip.setPixelColor(16, 255, 170, 0, 0);
              strip.setPixelColor(17, 255, 146, 0, 0);
              //orange
              strip.setPixelColor(18, 255, 121, 0, 0);
              strip.setPixelColor(19, 255, 97,  0, 0);
              strip.setPixelColor(20, 255, 73,  0, 0);
              //red
              strip.setPixelColor(21, 255, 48,  0, 0);
              strip.setPixelColor(22, 255, 24,  0, 0);
              strip.setPixelColor(23, 255, 16,  0, 0);
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
//    for (int c = 0; c < 30;c++){
//      strip.setPixelColor(c, 0, 0, 0, 0);
    }
  }
}


void liveGainMono () {
  if (fps > 24) {
    if (peak1.available()) {
      fps = 0;
      int monoPeak = peak1.read() * 31.0;
      Serial.println(monoPeak);
      for (int cnt = 0; cnt < 30; cnt++) {
        //change this so that it can go higher than 30 but if it does the to led is red instead of green
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

        //        delay(75);
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

//void monophonicAnalysis() {
//  if (notefreq.available()) {
//    float note = notefreq.read();
//    float prob = notefreq.probability();
//    Serial.printf("Note: %3.2f | Probability: %.2f\n", note, prob);
//  }
//}



//5x5 array representing the 5 rows of 5 leds I'll use
//int npLights[5][5] = {
//  {, , , ,},
//  {, , , ,},
//  {, , , ,},
//  {, , , ,},
//  {, , , ,}
//};
