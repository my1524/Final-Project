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



/*
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

*/



