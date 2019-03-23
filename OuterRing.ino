

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 37

#define CIRCLEPIN 8

#define NUM_LEDS 30

#define MIDDLEPIN 0

#define NUM_LEDS_CIRCLE 12

#define NUM_LEDS_MIDDLE 7

#define BRIGHTNESS 10

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel circle = Adafruit_NeoPixel(NUM_LEDS_CIRCLE, CIRCLEPIN, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel middle = Adafruit_NeoPixel(NUM_LEDS_MIDDLE, MIDDLEPIN, NEO_GRBW + NEO_KHZ800);


bool mSSwitchState, mSSwitchStateLast; //monoStereoSwitch

elapsedMillis fps;
elapsedMillis circleSeconds;
elapsedMillis middleSeconds;

void audioSetup() {
  AudioMemory(12);
  strip.setBrightness(BRIGHTNESS);
  strip.begin();
  strip.show();
  circle.setBrightness(BRIGHTNESS);
  circle.begin();
  circle.show();
  middle.setBrightness(BRIGHTNESS);
  middle.begin();
  middle.show();
  mSSwitchState = digitalRead(monoStereoPin);
}
//this tests to see if the mono/stereo switch is on or off and returns if it has just been switched on
bool checkSwitch() {
  mSSwitchStateLast = mSSwitchState;
  mSSwitchState = digitalRead(monoStereoPin);
  if (mSSwitchState == HIGH) {
    return HIGH;
  }
  else  {
    return LOW;
  }
}
int h;
int l;
int m;

// this function makes the leds light up based on amplitude in stereo
void liveGainStereo () {
  if (fps > 24) {
    if (peak1.available() && peak2.available()) {
      fps = 0;
      int leftPeak = peak1.read() * 16.0;
      int rightPeak = peak2.read() * 16.0;

      Serial.println(leftPeak);
      Serial.println(rightPeak);
      Serial.println();
      for (int cnt = 0; cnt < 15; cnt++) {
        if (cnt < leftPeak - 1 || cnt < rightPeak - 1) {
          //this loop sets the top several LEDs to gradate from yellow to red if the signal is peaking
          if (cnt > 13 && leftPeak > 15) {
            //yellow
            strip.setPixelColor(6, 255, 195, 0, 0);
            strip.setPixelColor(7, 255, 170, 0, 0);
            strip.setPixelColor(8, 255, 146, 0, 0);
            //orange
            strip.setPixelColor(9, 255, 121, 0, 0);
            strip.setPixelColor(10, 255, 97,  0, 0);
            strip.setPixelColor(11, 255, 73,  0, 0);
            //red
            strip.setPixelColor(12, 255, 48,  0, 0);
            strip.setPixelColor(13, 255, 24,  0, 0);
            strip.setPixelColor(14, 255, 16,  0, 0);
            strip.show();
    //        whiteCircle(cnt);
            whiteCircleR();
          }
          else {
            strip.setPixelColor(cnt, 30, 195, 18, 0);
            strip.show();
            randomCircle();
            randomMiddle();
          }
          if (cnt > 13 && rightPeak > 15) {
            //yellow
            strip.setPixelColor(23, 255, 195, 0, 0);
            strip.setPixelColor(22, 255, 170, 0, 0);
            strip.setPixelColor(21, 255, 146, 0, 0);
            //orange
            strip.setPixelColor(20, 255, 121, 0, 0);
            strip.setPixelColor(19, 255, 97,  0, 0);
            strip.setPixelColor(18, 255, 73,  0, 0);
            //red
            strip.setPixelColor(17, 255, 48,  0, 0);
            strip.setPixelColor(16, 255, 24,  0, 0);
            strip.setPixelColor(15, 255, 16,  0, 0);
            strip.show();
       //     whiteCircle(cnt);
            whiteCircleL();
          }
          else {
            strip.setPixelColor(29 - cnt, 30, 195, 18, 0);
            strip.show();
            randomCircle();
            randomMiddle();
          }




        }
        else
        {
          strip.setPixelColor(cnt, 0, 0, 0, 0);
          strip.setPixelColor(29 - cnt, 0, 0, 0, 0);
          strip.show();
          randomCircle();
          randomMiddle();
        }
      }

    }

  }

  delay(10);
}

//this does the same as above except with a mono signal, using all 30 LEDs 
void liveGainMono () {

  
 /* for (int x = 0; x <NUM_LEDS_CIRCLE; x++){
      circle.setPixelColor(x, 0, 0, 0, 255);
  }
  */
  circle.show();
 // delay (10);
  if (fps > 24) {
    if (peak1.available()) {
      fps = 0;
      int monoPeak = peak1.read() * 31.0;
      Serial.println(monoPeak);
      for (int cnt = 0; cnt < 30; cnt++) {
        if (cnt < monoPeak - 1 ) {
          if (cnt > 28 && monoPeak > 30) {
            //yellow
            strip.setPixelColor(21, 255, 195, 0, 0);
            strip.setPixelColor(22, 255, 170, 0, 0);
            strip.setPixelColor(23, 255, 146, 0, 0);
            //orange
            strip.setPixelColor(24, 255, 121, 0, 0);
            strip.setPixelColor(25, 255, 97,  0, 0);
            strip.setPixelColor(26, 255, 73,  0, 0);
            //red
            strip.setPixelColor(27, 255, 48,  0, 0);
            strip.setPixelColor(28, 255, 24,  0, 0);
            strip.setPixelColor(29, 255, 16,  0, 0);
            strip.show();
      //      whiteCircle(cnt);
            whiteCircle2();
          }
          else {
            strip.setPixelColor(cnt, 30, 195, 18, 0);
            strip.show();
            randomCircle();
            randomMiddle();
          }

        }
        else
        {
          strip.setPixelColor(cnt, 0, 0, 0, 0);
          strip.show();
          randomCircle();
          randomMiddle();
        }
      }
    }

    delay(10);
  }

}







/*
void pixelLoop() {

  for (i; i < NUM_LEDS; i++) {
    if (i % 4 == 0){
      circle.setPixelColor(i, 255, 128, 0, 0);
      circle.show();
      delay(75);
    }
    else if (i % 3 == 0) {
      circle.setPixelColor(i, 240, 25, 120, 0);
      circle.show();
      delay(75);
    }
    else if (i % 2 ==0){
      circle.setPixelColor(i, 153, 0, 153, 0);
      circle.show();
      delay(75);
    }
    else {
      circle.setPixelColor(i, 0, 0, 255, 0);
      circle.show();
      delay(75);
    }
  }
    i = i-NUM_LEDS+1;
}
*/
void whiteStrand(){
  for (int x = 0; x <NUM_LEDS; x++){
      circle.setPixelColor(x, 255, 5, 167, 0);
      circle.show();
      delay (100);
  }
  
  
}

void randomCircle(){

    if (circleSeconds > 250) {
      circleSeconds = 0;  
 //     Serial.println(l+100);

          
      if (l > 11) {
        l = 0;
        offCircle();
      }
      
  //most random
      circle.setPixelColor(l, random(255), random(255), random(255), 0);
    //pink random
    //circle.setPixelColor(n, random(100, 255), random(150), random(75, 175), 0);
      circle.show();
      l++;

      
    }
    else {
    }
//    Serial.println(l);
//    h++;
}
void randomMiddle(){
//  Serial.println("we are in middle");
    if (middleSeconds > 250) {
      middleSeconds = 0;  
 //     Serial.println(l+100);

          
      if (m > 6) {
        m = 0;
        offMiddle();
      }
      
  //most random
      middle.setPixelColor(m, random(255), random(255), random(255), 0);
    //pink random
    //circle.setPixelColor(n, random(100, 255), random(150), random(75, 175), 0);
      middle.show();
      m++;

    }
    else {
    }
//    Serial.println(l);
//    h++;

}
void whiteCircle(int cnt){
  circle.setPixelColor(cnt, 0, 0, 0, 255);
  circle.show();
  
  /*
  for (int r = 0; NUM_LEDS_CIRCLE; r) {
    circle.setPixelColor(r, 0, 0, 0, 255);
    circle.show();
  }
  */

}
void whiteCircle2(){
    circle.setPixelColor(0, 0, 0, 0, 255);
    circle.setPixelColor(1, 0, 0, 0, 255);
    circle.setPixelColor(2, 0, 0, 0, 255);
    circle.setPixelColor(3, 0, 0, 0, 255);
    circle.setPixelColor(4, 0, 0, 0, 255);
    circle.setPixelColor(5, 0, 0, 0, 255);
    circle.setPixelColor(6, 0, 0, 0, 255);
    circle.setPixelColor(7, 0, 0, 0, 255);
    circle.setPixelColor(8, 0, 0, 0, 255);
    circle.setPixelColor(9, 0, 0, 0, 255);
    circle.setPixelColor(10, 0, 0, 0, 255);
    circle.setPixelColor(11, 0, 0, 0, 255);
    circle.setPixelColor(12, 0, 0, 0, 255);
    circle.show();

}

void whiteCircleL(){
    circle.setPixelColor(6, 0, 0, 0, 255);
    circle.setPixelColor(7, 0, 0, 0, 255);
    circle.setPixelColor(8, 0, 0, 0, 255);
    circle.setPixelColor(9, 0, 0, 0, 255);
    circle.setPixelColor(10, 0, 0, 0, 255);
    circle.setPixelColor(11, 0, 0, 0, 255);
    circle.setPixelColor(12, 0, 0, 0, 255);
    circle.show();

}
void whiteCircleR(){
    circle.setPixelColor(0, 0, 0, 0, 255);
    circle.setPixelColor(1, 0, 0, 0, 255);
    circle.setPixelColor(2, 0, 0, 0, 255);
    circle.setPixelColor(3, 0, 0, 0, 255);
    circle.setPixelColor(4, 0, 0, 0, 255);
    circle.setPixelColor(5, 0, 0, 0, 255);
    circle.show();

}

void offCircle(){
  int v = 25;
    circle.setPixelColor(0, 0, 0, 0, v);
    circle.setPixelColor(1, 0, 0, 0, v);
    circle.setPixelColor(2, 0, 0, 0, v);
    circle.setPixelColor(3, 0, 0, 0, v);
    circle.setPixelColor(4, 0, 0, 0, v);
    circle.setPixelColor(5, 0, 0, 0, v);
    circle.setPixelColor(6, 0, 0, 0, v);
    circle.setPixelColor(7, 0, 0, 0, v);
    circle.setPixelColor(8, 0, 0, 0, v);
    circle.setPixelColor(9, 0, 0, 0, v);
    circle.setPixelColor(10, 0, 0, 0, v);
    circle.setPixelColor(11, 0, 0, 0, v);
    circle.setPixelColor(12, 0, 0, 0, v);
    circle.show();
}
void offMiddle(){
  int v = 25;
    middle.setPixelColor(0, 0, 0, 0, v);
    middle.setPixelColor(1, 0, 0, 0, v);
    middle.setPixelColor(2, 0, 0, 0, v);
    middle.setPixelColor(3, 0, 0, 0, v);
    middle.setPixelColor(4, 0, 0, 0, v);
    middle.setPixelColor(5, 0, 0, 0, v);
    middle.setPixelColor(6, 0, 0, 0, v);
    
}

void whiteMiddle(){
  int v = 255;
    middle.setPixelColor(0, 0, 0, 0, v);
    middle.setPixelColor(1, 0, 0, 0, v);
    middle.setPixelColor(2, 0, 0, 0, v);
    middle.setPixelColor(3, 0, 0, 0, v);
    middle.setPixelColor(4, 0, 0, 0, v);
    middle.setPixelColor(5, 0, 0, 0, v);
    middle.setPixelColor(6, 0, 0, 0, v);
    middle.show();
}


