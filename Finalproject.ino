
bool checkedAudio = false;
int monoStereoPin = 32;
bool checkedSwitch;

void setup() {
  audioSetup();
  pinMode (monoStereoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  //this checks the position of the mono/stereo switch
  checkedSwitch=checkSwitch();
  //this is fft testing bin stuff
  //  analyzeAudio();
  //  binAnalysis();
  //  delay(1000);

  // pixelLoop();
  //I need to create a check button thing for this 
  if (checkedSwitch == HIGH ) {
    liveGainMono();
  }
  else {
    liveGainStereo();
  }
  return;
  //
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

