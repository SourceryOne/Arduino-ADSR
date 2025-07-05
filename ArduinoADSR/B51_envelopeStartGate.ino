//250619 added switches for all the cvcontrol with default instead of case==0. Needs to be done for trig, loop and nloop aswell :/

//CHANNEL 1
void envelopeStartGate1() {
  //GATE ON
  if (gate1Active==1) { 
    if (envelope1Phase==0 || envelope1Phase==4) { //start the envelope
      envelope1Phase=1; //Set the phase to Attack 
      //if (CVcontrol==1) {
      //    rampDuration1 = attackValueCh1wCV * attack1Multiplier; //attackValueCh1 is set in the checkPots() function, attack multiplier set in the menu from fixed values in the config file.
      //} else {
      //    rampDuration1 = attackValueCh1 * attack1Multiplier; //attackValueCh1 is set in the checkPots() function, attack multiplier set in the menu from fixed values in the config file.
      //}
      //Use switch instead, as it should be faster? 250619
      switch (CVcontrol) {
        case 1: 
          rampDuration1 = attackValueCh1wCV * attack1Multiplier; //attackValueCh1 is set in the checkPots() function, attack multiplier set in the menu from fixed values in the config file.
          break;
        case 5: 
          rampDuration1 = attackValueCh1wCV * attack1Multiplier; //attackValueCh1 is set in the checkPots() function, attack multiplier set in the menu from fixed values in the config file.
          break;
        default:
          rampDuration1 = attackValueCh1 * attack1Multiplier; //attackValueCh1 is set in the checkPots() function, attack multiplier set in the menu from fixed values in the config file.
          break;
      }
      startTime1 = millis();  // Record the start time
      currentValue1 = 0;
    } else if (envelope1Phase==12) {
      //MOVE TO DECAY
      envelope1Phase=2; 
      currentValue1 = maxValueCh1;
      switch (CVcontrol) {
        //case 0: USE DEFAULT INSTEAD. 250619
          //rampDuration1 = decayValueCh1 * decay1Multiplier;
          //break;
        case 2:
          rampDuration1 = decayValueCh1wCV * decay1Multiplier;
          break;
        case 6:
          rampDuration1 = decayValueCh1wCV * decay1Multiplier;
          break;
        default:
          rampDuration1 = decayValueCh1 * decay1Multiplier;
          break;
      }
      startTime1 = millis();       
    } else if (envelope1Phase==23) {
      //MOVE TO SUSTAIN
      envelope1Phase=3;
      switch (CVcontrol) {
        //case 0: USE DEFAULT INSTEAD 250619
          //currentValue1 = sustainValueCh1*sustainMultiplier;
          //break;
        case 3:
          currentValue1 = sustainValueCh1wCV*sustainMultiplier;
          break;
        case 7:
          currentValue1 = sustainValueCh1wCV*sustainMultiplier;
          break;
        default:
          currentValue1 = sustainValueCh1*sustainMultiplier;
          break;
      }
    }
  } else { //NO GATE
    if (envelope1Phase>0 && envelope1Phase<=3) { envelope1Phase=34; }
    if (envelope1Phase==34) { //inbetween sustain and release
      //MOVE TO RELEASE
      envelope1Phase=4;
      startingValueRelease1 = currentValue1;
      switch (CVcontrol) {
        //case 0: USE DEFAULT INSTEAD 250619
          //rampDuration1 = releaseValueCh1 * release1Multiplier; 
          //break;
        case 4:
          rampDuration1 = releaseValueCh1wCV * release1Multiplier;
          break;
        case 8:
          rampDuration1 = releaseValueCh1wCV * release1Multiplier;
          break;
        default: 
          rampDuration1 = releaseValueCh1 * release1Multiplier; 
          break;
      }
      startTime1 = millis();       
    }
  }
}


//CHANNEL 2
void envelopeStartGate2() {
  //TURN OFF THIS WHOLE THING IF WE ARE IN OTHER MODE.
  //GATE ON
  if (gate2Active || (moduleMode==2 && gate1Active)) {
    if (envelope2Phase==0 || envelope2Phase==4) { //start the envelope
      envelope2Phase=1; //Set the phase to Attack 
      rampDuration2 = attackValueCh2 * attack2Multiplier; //attackValueCh1 is set in the checkPots() function, attack multiplier set in the menu from fixed values in the config file.
      startTime2 = millis();  // Record the start time
    } else if (envelope2Phase==12) {
      //MOVE TO DECAY
      envelope2Phase=2; 
      currentValue2 = maxValueCh2;
      rampDuration2 = decayValueCh2 * decay2Multiplier;
      startTime2 = millis();       
    } else if (envelope2Phase==23) {
      //MOVE TO SUSTAIN
        envelope2Phase=3;
        currentValue2 = sustainValueCh2*sustainMultiplier;                                 // *32 ändra om man vill göra till 64000 eller annat!
    }
  } else { //NO GATE
    if (envelope2Phase>0 && envelope2Phase<=3) { envelope2Phase=34; }
    if (envelope2Phase==34) { //inbetween sustain and release
      //MOVE TO RELEASE
      envelope2Phase=4; 
      startingValueRelease2 = currentValue2;
      rampDuration2 = releaseValueCh2 * release2Multiplier; 
      startTime2 = millis();       
    }
  }
}
