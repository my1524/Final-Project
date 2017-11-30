
bool checkedAudio = false;

void setup() {
  audioSetup();
  Serial.begin(9600);
}

void loop() {
 //this is fft testing bin stuff
//  analyzeAudio();
//  binAnalysis();
//  delay(1000);
  
  // pixelLoop();
  liveGainStereo();
  return;
  
  checkedAudio = audioChecker();
  if (checkedAudio == true) {
    //   pixelLoop();
  }
  else {
    // whiteStrand();
  }
}

/*connect sine wave to program through crazy amount of resistors,
   print out just if it's loud
*/

