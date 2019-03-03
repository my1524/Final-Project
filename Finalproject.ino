bool checkedAudio = false;
int monoStereoPin = 32;
bool checkedSwitch;


void setup() {
  audioSetup();
  pinMode (monoStereoPin, INPUT);
  potSetup();
  Serial.begin(9600);
}

void loop() {
 // whiteStrand();
 //this runs the pot test
  potLoop(); 
  //this checks the position of the mono/stereo switch

  /*
  if (checkSwitch() ) {
    liveGainMono();
  }
  else {
    liveGainStereo();
  }
  return;
 
  */
}



