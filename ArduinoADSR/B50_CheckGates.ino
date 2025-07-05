void checkGates() {
  //Gate1
  if (!digitalRead(gatein1)) { //becuase we have input_pullup, so it is HIGH when no input.
    //gate1 is active
    gate1Active=1; 
  } else {
    //gate1 is not active
    gate1Active=0;
    if (EndOfCh1>0) { gate2Active=0; } //Add also to keep it open if it is before sustain and sustain1 is active.
  }

  //Gate2
  //ONLY CHECK GATE2 IF WE ARE IN CORRECT MODE!?
  //END OF ... FUNCTIONALITY.
  switch (EndOfCh1) {
    case 0:
      if (!digitalRead(gatein2)) { //If we dont use EndOf, check the 2nd gate.
        //gate1 is active, but if we are in CV mode then we dont use the gate, so a quick check to see if CVcontrol is 0 which means we dont use CV...
        if (CVcontrol==0) {
          gate2Active=1;
        } 
      } else {
        //gate2 is not active
        gate2Active=0;
      }
      break; //Do nothing, leave Ch2 to its own.
    case 1: //ATTACK
      if (envelope1Phase==12) { gate2Active=1; } //force Envelope2 to start. Should be in trig or nLoop to work best...
      break;
    case 2: //DECAY
      if (envelope1Phase==23) { gate2Active=1; } //force Envelope2 to start. Should be in trig or nLoop to work best...
      if (envelope1Phase==3)  { gate2Active=1; } //This should keep the gate2 envelope active while Ch1 Sustain is pressed. 250619
      break;
    case 3: //SUSTAIN
      if (envelope1Phase==34) { gate2Active=1; } //force Envelope2 to start. Should be in trig or nLoop to work best...
      break;
    case 4: //RELEASE
      if (envelope1Phase==40) { 
          gate2Active=1; //force Envelope2 to start. Should be in trig or nLoop to work best...
          //envelope1Phase=0; //set the envelopephase to 0 for envelope 1. NOT NEEDED,  FIXED IN THE LOOP().
      } 
      break;
  }
}







  
  
