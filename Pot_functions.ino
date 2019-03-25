
//this is example code modified 

//same problem wth results with either of the following used
int potPin = A12;  // Analog input pin that the potentiometer is attached to
//#define potPin 31
//const int analogOutPin = 12; // Analog output pin that the LED is attached to

int potValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)


int buttonPin1 = 1;
int buttonPin2 = 2;
boolean lastButtonState1 = LOW;
boolean lastButtonState2 = LOW;
boolean buttonState1 = LOW;
boolean buttonState2 = LOW;
int outputValueWas = 0;
int currentLED = 0;

void potSetup() {
  
    pinMode(potPin, INPUT);
    pinMode(buttonPin1, INPUT);
    pinMode(buttonPin2, INPUT);
}

int getButtonInfo() {
  lastButtonState1 = buttonState1;
  buttonState1 = digitalRead(buttonPin1);
  //determines if setting mode is on
  if (buttonState1 == HIGH && lastButtonState1 == LOW) {
    Serial.println("pushedsadfjaslkdjfasjdfhasjdfasdjkfas");
    if (inSettingMode == false){
      inSettingMode = true;
    //  delay(1000);
      Serial.println("delay over");
      //this ensures you can go back to the setting you were previously on until I add more
     // outputValueWas = outputValue;
    //  outputValue = 25;
    }
    // if in setting mode, do the following
    else {
      outputValue = chooseOptionNumber();
      inSettingMode = false;
    //  outputValue = outputValueWas;
   //   delay(1000);

    }
  }//end of if buttonstate1 high and lastbuttonstate1 ow
  
  //turns center rainbow to indicate setting mode is on
  if (inSettingMode == true){
    rainbowMiddle();
  }
//for testing purposes
  Serial.println(inSettingMode);
  return outputValue;
}


int chooseOptionNumber() {
  lastButtonState2 = buttonState2;
  buttonState2 = digitalRead(buttonPin2);
  Serial.print ("current lit LED is");
  Serial.println (currentLED);
  if (buttonState2 == HIGH && lastButtonState2 == LOW){
    currentLED++;
    if (currentLED == 12){
      currentLED = 0;
    }
    Serial.print("current LED changed, now ");
    Serial.println (currentLED);
  }
    circle.setPixelColor(currentLED, 0, 255, 0, 0);
      circle.show();
      return currentLED;
}


//the following are pot functions that can't be used with the adc
//
//int potPosition(){
//  //it doesn't get past potValue the second time and not the first time if Serial.println("marker1 "); is commented out
//  Serial.println("marker1 ");
//  potValue = analogRead(A0);
//  Serial.println("hello world ");
//  outputValue = map(potValue, 0, 1023, 0, 11);
//  Serial.print("value is ");
//  Serial.println(outputValue);
//  return outputValue;
//  delay(2000);
//}


//void potTest() {
//
//  // read the analog in value:
//  Serial.println(potValue);
//  potValue = analogRead(potPin);
//  Serial.print(potValue);
//  // map it to the ra nge of the analog out:
//  outputValue = map(potValue, 0, 1023, 0, 11);
//  // change the analog out value:
// // analogWrite(analogOutPin, outputValue);
//
//  // print the results to the Serial Monitor:
//  Serial.print("sensor = ");
//  Serial.print(potValue);
//  Serial.print("\t output = ");
//  Serial.println(outputValue);
//
//  // wait 2 milliseconds before the next loop for the analog-to-digital
//  // converter to settle after the last reading:
//  delay(2);
//
// return;
//}

