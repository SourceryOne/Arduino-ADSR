// Include the configuration header file
#include "Config.h"

/*
 * Be adviced that this code will not be able to work in the "final" design, as it should implement two independent ADSRs and this code just runs linearily, it has to be more looped with all functions running all the time...
 * But for now this is just testing so it all works.
 */
// Define the target value and the ramp duration
const long maxValue = 65536;    // The maximum value we want to reach ... A 16-bit register can store 216 different values. The signed range of integer values that can be stored in 16 bits is −32,768 (−1 × 215) through 32,767 (215 − 1); the unsigned range is 0 through 65,535 (216 − 1).
int rampDuration = 1000; // Ramp duration in milliseconds (1 second)

int trig1active=0;
int trig1state=0;

int sustainLevel=0;

void setup() {
  //PINSETUP
  pinMode(redPWM, OUTPUT);
  pinMode(greenPWM, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(9,OUTPUT); //OUTPUT2A
  pinMode(10,OUTPUT);  //OUTPUT2B
  pinMode(11,OUTPUT); //OUTPUT1A
  pinMode(3,OUTPUT); //OUTPUT1B
  
  pinMode(gatein1, INPUT_PULLUP);
  pinMode(gatein2, INPUT_PULLUP);

    TCCR1A = B10100001;  //Setting COM0A1,COM0A0, COM0B1, COM0B0 to 10 and 10 for Clear on compare set to bottom. And the WGM11 and WGM10 bits to 01 (along with WGM12 and WGM13 set to 00 in TCCR1B) for Phase correct PWM, 8 bit. (32kHz)
    //            v- set to 1 for 8 bit Fast PWM (64kHz)                     
    TCCR1B = B00000001; // Setting the WGM12 and WGM13 to 00 (see comments for TCCR1A above), and CS00, CS01, and CS02 bits for Prescaler /1 (001) 

    TCCR2A = B10100001;  //Setting COM0A1,COM0A0, COM0B1, COM0B0 to 10 and 10 for Clear on compare set to bottom. And the WGM11 and WGM10 bits to 01 (along with WGM12 and WGM13 set to 00 in TCCR1B) for Phase correct PWM, 8 bit. (32kHz)
    //            v- set to 1 for 8 bit Fast PWM (64kHz)                     
    TCCR2B = B00000001; // Setting the WGM12 and WGM13 to 00 (see comments for TCCR1A above), and CS00, CS01, and CS02 bits for Prescaler /1 (001) 

 
  //SETTING INITAL VALUES
  OCR1A = 0;
  OCR1B = 0;
   


    pinMode(13,OUTPUT);

    
}

void loop() {
  //read the pots from time to time...

  //below should only be done if it is the correct channel... or set the channel and use this same loop for both channels but different outputs. (ofcourse both outputs at the same time!

  trig1state=digitalRead(gatein1);
  if (trig1state==0  && trig1active==0) {
  
    //ATTACK
    //trig1active=1;
    digitalWrite(led1,LOW);
    digitalWrite(led2,HIGH);
    digitalWrite(led3,HIGH);
    digitalWrite(led4,HIGH);
    
    rampDuration=analogRead(attackPot);
    long startTime = millis();  // Record the start time

    // Ramp from 0 to maxValue over the course of rampDuration
    while (millis() - startTime < rampDuration) {
      if (digitalRead(gatein1)) {
        break;
      }
      // Calculate the elapsed time
      long elapsedTime = millis() - startTime;
      // Calculate the current ramp value based on the elapsed time
      long currentValue = map(elapsedTime, 0, rampDuration, 0, maxValue);
      OCR1A = highByte(currentValue);
      OCR1B = lowByte(currentValue);

      OCR2A = highByte(currentValue);
      OCR2B = lowByte(currentValue);
      //send the value to the LED
      int ledValue = map(currentValue, 0, 65280, 0, 255);
      analogWrite(greenPWM, ledValue);
    }
    
    //DECAY
    digitalWrite(led1,HIGH);
    digitalWrite(led2,LOW);
    rampDuration=analogRead(decayPot);
    sustainLevel=map(analogRead(sustainPot),0,1024,0,maxValue);
    startTime = millis();  // Record the start time

    // Ramp from 0 to maxValue over the course of rampDuration
    while (millis() - startTime < rampDuration) {
      if (digitalRead(gatein1)) {
        break;
      }
      // Calculate the elapsed time
      long elapsedTime = millis() - startTime;
      // Calculate the current ramp value based on the elapsed time
      
      long currentValue = map(elapsedTime, 0, rampDuration, maxValue, sustainLevel);
      OCR1A = highByte(currentValue);
      OCR1B = lowByte(currentValue);

      OCR2A = highByte(currentValue);
      OCR2B = lowByte(currentValue);
      //send the value to the LED
      int ledValue = map(currentValue, 0, 65280, 0, 255);
      analogWrite(greenPWM, ledValue);
    }
    //OCR1A = highByte(sustainLevel);
    //OCR1B = lowByte(sustainLevel);
    
    //SUSTAIN
    digitalWrite(led2,HIGH);
    digitalWrite(led3,LOW);
    while (trig1state==0) {
      if (digitalRead(gatein1)) {
        break;
      }  
      trig1state=digitalRead(gatein1);
      //sustainLevel=analogRead(sustainPot);
      sustainLevel=map(analogRead(sustainPot),0,1024,0,maxValue);
    
      OCR1A = highByte(sustainLevel);
      OCR1B = lowByte(sustainLevel);

      OCR2A = highByte(sustainLevel);
      OCR2B = lowByte(sustainLevel);
      int ledValue = map(sustainLevel, 0, 65280, 0, 255);
      analogWrite(greenPWM, ledValue);
    }

    //RELEASE
    digitalWrite(led3,HIGH);
    digitalWrite(led4,LOW);
    rampDuration=analogRead(releasePot);
    startTime = millis();  // Record the start time

    // Ramp from 0 to maxValue over the course of rampDuration
    while (millis() - startTime < rampDuration) {
      // Calculate the elapsed time
      long elapsedTime = millis() - startTime;
      // Calculate the current ramp value based on the elapsed time
      long currentValue = map(elapsedTime, 0, rampDuration, sustainLevel, 0 );
      OCR1A = highByte(currentValue);
      OCR1B = lowByte(currentValue);

      OCR2A = highByte(currentValue);
      OCR2B = lowByte(currentValue);
      //send the value to the LED
      int ledValue = map(currentValue, 0, 65280, 0, 255);
      analogWrite(greenPWM, ledValue);
    }


    digitalWrite(led1,HIGH);
    digitalWrite(led2,HIGH);
    digitalWrite(led3,HIGH);
    digitalWrite(led4,HIGH);
  }
  OCR1A = 0;
  OCR1B = 0;
  // Pause after completing the ramp for clarity
  //delay(1000);  // 1-second delay before restarting
  
}
