
bool checkedAudio = false;

void setup() {
  pixelSetup();
  Serial.begin(9600);
}

void loop() {
  analyzeAudio();
  binAnalysis();
  delay(1000);
  
//  // pixelLoop();
//  liveGain();
//  return;
//  checkedAudio = audioChecker();
//  if (checkedAudio == true) {
//    //   pixelLoop();
//  }
//  else {
//    // whiteStrand();
//  }
}

/*connect sine wave to program through crazy amount of resistors,
   print out just if it's loud
*/

