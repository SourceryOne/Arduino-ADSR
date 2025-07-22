//CHANNEL 1
void envelopeWrite1() {

  //CALCULATING currentValue1
  unsigned long elapsedTime1 = millis() - startTime1;
  if (elapsedTime1 < rampDuration1) {
    if (envelope1Phase==1) { 
      float progress = (float)elapsedTime1 / rampDuration1; 
      currentValue1 = maxValueCh1 * pow(progress, attack1Exponent); }
    if (envelope1Phase==2) { 
      float progress = (float)elapsedTime1 / rampDuration1; 
      switch (CVcontrol) {
        case 3:
          currentValue1 = sustainValueCh1wCV*sustainMultiplierCh1 + (maxValueCh1 - sustainValueCh1wCV*sustainMultiplierCh1) * pow(1.0 - progress, decay1Exponent); 
          break;
        default:      
          currentValue1 = sustainValueCh1*sustainMultiplierCh1 + (maxValueCh1 - sustainValueCh1*sustainMultiplierCh1) * pow(1.0 - progress, decay1Exponent); 
          break;
      }
    } 
    if (envelope1Phase==3) { 
      switch (CVcontrol) {
        case 3:
          currentValue1=sustainValueCh1wCV*sustainMultiplierCh1; 
          break;
        default:      
          currentValue1=sustainValueCh1*sustainMultiplierCh1; 
          break;
      }
    }
    if (envelope1Phase==4) { 
      float progress = (float)elapsedTime1 / rampDuration1; 
      //there is a drop in amplitude, larger the lower the sustain is... Why?
      currentValue1 = (sustainValueCh1*sustainMultiplierCh1) * pow(1.0 - progress, release1Exponent);
    }
  } else { //ENVELOPE PHASE TIME IS UP!
    if (envelope1Phase==1) {
      currentValue1 = maxValueCh1;  // Ensure it stays at maxValue after 1000ms OR SHOULD IT BE THE TOP OF SUSTAIN IF DECAY IS OFF!
      envelope1Phase=12; //move to next phase.
    } else if (envelope1Phase==2) { 
      //currentValue1 = sustainValueCh1*sustainMultiplier; 
      envelope1Phase=23;
    } else if (envelope1Phase==3) {
        switch (CVcontrol) {
          case 3:
            currentValue1=sustainValueCh1wCV*sustainMultiplierCh1; 
            break;
          default:      
            currentValue1=sustainValueCh1*sustainMultiplierCh1; 
            break;
        }        
    } else if (envelope1Phase==4) { 
      currentValue1 = 0; 
      //envelope1Phase=0;
      envelope1Phase=40; //added for EndOfRelease to work.
      
      //nDecay stuff, if we are in nLoop mode:
      if (actCh1==3) {
        //if nloop is active, and nllops are less than max loops or gate is on and loops are 0 then do below ELSE set to originalValues.
        if ((nLoop1Count<=nLoopLengthCh1) || (nLoopLengthCh1==0 && gate1Active==1)) {
          if (nLoopDecayCh1>0) { //0=no decay. fix leds so it is off when 0.
            maxValueCh1 -= (maxValueCh1 >> nLoopDecayCh1); //bitwise operation works better on large values
            sustainMultiplierCh1 -= (sustainMultiplierCh1 >> nLoopDecayCh1); 
            // Stop if it gets very low
            if (maxValueCh1 < 1) maxValueCh1 = 1;
            if (sustainMultiplierCh1 < 1) sustainMultiplierCh1 = 1;
          }
        } else { //So now the nLoop is done and we can set the originalMaxValue back and wait for something?
            nLoop1Count=0; //Leave this the the nloopenvelopestart
            //MOVED IN HERE TO SEE IF THAT WORKS
            //SEEMS TO WORK SOMETIMES, if you hold the gate until the nloops are finished... otherwise no. it runs irt one more time setting it one decay lower...
            //But this SHOULD work as it is the end of the loop (phase 40)...?
            nLoop1Active=0;
            maxValueCh1=maxValue; //or originalMaxValue if we keep that variable?
            sustainMultiplierCh1=sustainMultiplier; //or originalSustainMultiplier if we keep that variable.
        }
      }
    }  
  }
    
  //Write the currentValue1
  OCR2A = highByte(currentValue1);
  OCR2B = lowByte(currentValue1);

  if (moduleMode==1) {
    //Also write ADSR1 to output2 if we are in moduleMode 1.
    OCR1A = highByte(currentValue1);
    OCR1B = lowByte(currentValue1);
  }
}




//CHANNEL 2
void envelopeWrite2() {
  //CALCULATING currentValue2
  unsigned long elapsedTime2 = millis() - startTime2;
  if (elapsedTime2 < rampDuration2) {
    if (envelope2Phase==1) { 
      float progress = (float)elapsedTime2 / rampDuration2; 
      currentValue2 = maxValueCh2 * pow(progress, attack2Exponent); }
    if (envelope2Phase==2) { 
      float progress = (float)elapsedTime2 / rampDuration2; 
      currentValue2 = sustainValueCh2*sustainMultiplierCh2 + (maxValueCh2 - sustainValueCh2*sustainMultiplierCh2) * pow(1.0 - progress, decay2Exponent); 
    } 
    if (envelope2Phase==3) { 
      currentValue2=sustainValueCh2*sustainMultiplierCh2; 
    }
    if (envelope2Phase==4) { 
      float progress = (float)elapsedTime2 / rampDuration2; 
      currentValue2 = (sustainValueCh2*sustainMultiplierCh2) * pow(1.0 - progress, release2Exponent); }
  } else { //ENVELOPE PHASE TIME IS UP!
    if (envelope2Phase==1) {
      currentValue2 = maxValueCh2;  // Ensure it stays at maxValue after 1000ms OR SHOULD IT BE THE TOP OF SUSTAIN IF DECAY IS OFF!
      envelope2Phase=12; //move to next phase.
    } else if (envelope2Phase==2) { 
      //currentValue2 = sustainValueCh2*sustainMultiplier; 
      envelope2Phase=23;
    } else if (envelope2Phase==3) {
        currentValue2=sustainValueCh2*sustainMultiplierCh2;         
    } else if (envelope2Phase==4) { 
      currentValue2 = 0; 
      //envelope2Phase=0;
      envelope2Phase=40; //added for EndOfRelease to work.
      
      //nDecay stuff, if we are in nLoop mode:
      if (actCh2==3) {
        //if nloop is active, and nllops are less than max loops or gate is on and loops are 0 then do below ELSE set to originalValues.
        if ((nLoop2Count<=nLoopLengthCh2) || (nLoopLengthCh2==0 && gate2Active==1)) {
          if (nLoopDecayCh2>0) { //0=no decay. fix leds so it is off when 0.
            maxValueCh2 -= (maxValueCh2 >> nLoopDecayCh2); //bitwise operation works better on large values
            sustainMultiplierCh2 -= (sustainMultiplierCh2 >> nLoopDecayCh2); 
            // Stop if it gets very low
            if (maxValueCh2 < 1) maxValueCh2 = 1;
            if (sustainMultiplierCh2 < 1) sustainMultiplierCh2 = 1;
          }
        } else { //So now the nLoop is done and we can set the originalMaxValue back and wait for something?
            nLoop2Count=0; //Leave this the the nloopenvelopestart
            //MOVED IN HERE TO SEE IF THAT WORKS
            //SEEMS TO WORK SOMETIMES, if you hold the gate until the nloops are finished... otherwise no. it runs irt one more time setting it one decay lower...
            //But this SHOULD work as it is the end of the loop (phase 40)...?
            nLoop2Active=0;
            maxValueCh2=maxValue; //or originalMaxValue if we keep that variable?
            sustainMultiplierCh2=sustainMultiplier; //or originalSustainMultiplier if we keep that variable.
        }
      }
    }  
  }

      
  //Write the value
  if (moduleMode!=1) {
    //But not if it is moduleMode 1
    OCR1A = highByte(currentValue2);
    OCR1B = lowByte(currentValue2);
  }
}
