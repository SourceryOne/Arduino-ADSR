void envelopeStartTrig1() {
  //GATE ON
  if (gate1Active==1) {
    if (envelope1Phase==0) { //remove this if for acting on falling edge.
      envelope1Phase=1; //Set the phase to Attack 
      rampDuration1 = attackValueCh1 * attack1Multiplier; //attackValueCh1 is set in the checkPots() function, attack multiplier set in the menu from fixed values in the config file.
      startTime1 = millis();  // Record the start time
      currentValue1 = 0;   
    }
  }
  if (envelope1Phase==12) {
    envelope1Phase=2; 
    currentValue1 = maxValue;
    rampDuration1 = decayValueCh1 * decay1Multiplier;
    startTime1 = millis();
  } else if (envelope1Phase==23) {
    //skip SUSTAIN and go directly to RELEASE
    envelope1Phase=4;
    startingValueRelease1 = sustainValueCh1*sustainMultiplier;
    rampDuration1 = releaseValueCh1 * release1Multiplier;
    startTime1 = millis();
  }
}


void envelopeStartTrig2() {
  //GATE ON
  if (gate2Active==1) {
    if (envelope2Phase==0) { 
      envelope2Phase=1; //Set the phase to Attack 
      rampDuration2 = attackValueCh2 * attack2Multiplier; //attackValueCh1 is set in the checkPots() function, attack multiplier set in the menu from fixed values in the config file.
      startTime2 = millis();  // Record the start time
      currentValue2 = 0; 
    }
  } 
  if (envelope2Phase==12) {
    envelope2Phase=2; 
    currentValue2 = maxValue;
    rampDuration2 = decayValueCh2 * decay2Multiplier;
    startTime2 = millis();
  } else if (envelope2Phase==23) {
    //skip SUSTAIN and go directly to RELEASE
    envelope2Phase=4;
    startingValueRelease2 = sustainValueCh2*sustainMultiplier;
    rampDuration2 = releaseValueCh2 * release2Multiplier;
    startTime2 = millis();
  }
}
