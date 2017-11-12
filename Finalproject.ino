#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputAnalog         adc1;           //xy=161,106
AudioAnalyzeFFT256       fft256_1;       //xy=361,110
AudioConnection          patchCord1(adc1, fft256_1);
// GUItool: end automatically generated code

//5x5 array representing the 5 rows of 5 leds I'll use
//int npLights[5][5] = {
//  {, , , ,},
//  {, , , ,},
//  {, , , ,},
//  {, , , ,},
//  {, , , ,}
//};

void setup() {
  // put your setup code here, to run once:
  simpleSetup();

}

void loop() {
  // put your main code here, to run repeatedly:
  simpleLoop();
}

/*connect sine wave to program through crazy amount of resistors,
   print out just if it's loud
*/
//function to analyze audio with fft
void analyzeAudio() {
}
