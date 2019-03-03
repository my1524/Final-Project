
//this is example code modified 

int potPin = A12;  // Analog input pin that the potentiometer is attached to
//const int analogOutPin = 12; // Analog output pin that the LED is attached to

int potValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

void potSetup() {
    pinMode(potPin, INPUT);
    
}

void potPosition(){
  
}


void potLoop() {
  // read the analog in value:
  Serial.println(potValue);
  potValue = analogRead(potPin);
  Serial.print(potValue);
  // map it to the range of the analog out:
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
//  delay(2);

 //return;
}

