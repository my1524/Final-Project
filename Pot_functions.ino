
//this is example code modified 

//same problem wth results with either of the following used
int potPin = A12;  // Analog input pin that the potentiometer is attached to
//#define potPin 31
//const int analogOutPin = 12; // Analog output pin that the LED is attached to

int potValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

void potSetup() {
    pinMode(potPin, INPUT);
}
int buttonPin1 = 1;
int buttonPin2 = 2;
boolean lastButtonState1 = LOW;
boolean lastButtonState2 = LOW;
boolean buttonState1 = LOW;
boolean buttonState2 = LOW;
boolean inSettingMode = false;


int getButtonInfo() {
  lastButtonState1 = buttonState1;
  buttonState1 = digitalRead(buttonPin1);
  lastButtonState2 = buttonState2;
  buttonState2 = digitalRead(buttonPin2);
  if (inSettingMode == true){
    whiteMiddle();
  }
  if (buttonState1 == HIGH && lastButtonState1 == LOW) {
    
  }
  
  return outputValue;
}


int potPosition(){
  //it doesn't get past potValue the second time and not the first time if Serial.println("marker1 "); is commented out
  Serial.println("marker1 ");
  potValue = analogRead(A0);
  Serial.println("hello world ");
  outputValue = map(potValue, 0, 1023, 0, 11);
  Serial.print("value is ");
  Serial.println(outputValue);
  return outputValue;
  delay(2000);
}


void potTest() {

  // read the analog in value:
  Serial.println(potValue);
  potValue = analogRead(potPin);
  Serial.print(potValue);
  // map it to the ra nge of the analog out:
  outputValue = map(potValue, 0, 1023, 0, 11);
  // change the analog out value:
 // analogWrite(analogOutPin, outputValue);

  // print the results to the Serial Monitor:
  Serial.print("sensor = ");
  Serial.print(potValue);
  Serial.print("\t output = ");
  Serial.println(outputValue);

  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(2);

 return;
}

