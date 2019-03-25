bool checkedAudio = false;
int monoStereoPin = 32;
bool checkedSwitch;
int optionNumber = 0;
boolean inSettingMode = false;

void setup() {
  audioSetup();
  pinMode (monoStereoPin, INPUT);
  potSetup();
  Serial.begin(9600);
}

void loop() {
//  rainbowMiddle();
  
//  Serial.println(optionNumber);
 // whiteStrand();
// this runs the pot test
//  optionNumber = potPosition();
// this is the button version of the pot selection
optionNumber = getButtonInfo(); //this is under Pot_functions tab
//  potTest(); 
//  Serial.println("got out of potPosition");
  //this checks the position of the mono/stereo switch
  if (optionNumber == 0){
      if (checkSwitch() ) {
      liveGainMono();
    }
    else {
      liveGainStereo();
    }
    
  }
  //this is the setting mode option for testing purposes
//  else if (optionNumber == 25){
// }
  else{
    Serial.print("option Number");
    Serial.println(optionNumber);
  }
  return;
}



