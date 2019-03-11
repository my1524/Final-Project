bool checkedAudio = false;
int monoStereoPin = 32;
bool checkedSwitch;
int optionNumber = 0;

void setup() {
  audioSetup();
  pinMode (monoStereoPin, INPUT);
  potSetup();
  Serial.begin(9600);
}

void loop() {
  
  Serial.println(optionNumber);
 // whiteStrand();
 //this runs the pot test
  optionNumber = potPosition();
//  potTest(); 
  Serial.println("got out of potPosition");
  //this checks the position of the mono/stereo switch
  if (optionNumber == 11){
    Serial.println("not running audio");
  }
  else{
  
      if (checkSwitch() ) {
      liveGainMono();
    }
    else {
      liveGainStereo();
    }
  }
  return;
}



