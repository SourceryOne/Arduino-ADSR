void envelopeStartnLoop1() {
  //GATE ON start the Loop once the Gate is activated.
  /*
  Ok, if gate is on, then play the amount of loops set by nLoopLengthCh1. if gate is released, continue to play until nLoop1Count>nLoopLengthCh1.
  IF nLoop1Count>nLoopLengthCh1 before the gate is released, then just wait for the gate to release, and then reset the counter.
  1. Wait for gate on.
  2a. Activate the loop.
  2b. Start counting loops  
  3a. Wait for end of nloops. OR    3b. Wait for end of gate
  4a. Wait for end of gate    OR    4b. Continue counting until end of nLoops.
  5. Reset counter.                 5. Reset counter.
 
  nLoop1Count++;
  nLoop1Active=1
  nLoopLengthCh1 
  */


  //1. Wait for gate on.
  if (gate1Active==1)  { // || nLoop1Active==1
    //2a. Activate the loop. Making sure we only activate the loop no counting now... And only start it if there are loops left in nLoop, OR if nLoopLengthChX is 0.
    if ((nLoop1Active==0 && nLoop1Count<nLoopLengthCh1) || nLoopLengthCh1==0) {
      nLoop1Active=1;
    }
  }
  if (nLoop1Active==1 && (nLoop1Count<=nLoopLengthCh1 || nLoopLengthCh1==0)) {
    if (envelope1Phase==0) {
      //2b. Count the loop.                    Could be done in 40 instead?
      nLoop1Count++;
      //START THE ENVELOPE.
      envelope1Phase=1; //Set the phase to Attack 
      rampDuration1 = attackValueCh1 * attack1Multiplier; //attackValueCh1 is set in the checkPots() function, attack multiplier set in the menu from fixed values in the config file.
      startTime1 = millis();  // Record the start time
      currentValue1 = 0; 
    }

  } 
  if (envelope1Phase==12) {
    envelope1Phase=2; 
    currentValue1 = maxValueCh1;
    rampDuration1 = decayValueCh1 * decay1Multiplier;
    startTime1 = millis();
  } else if (envelope1Phase==23) {
    //skip SUSTAIN and go directly to RELEASE
    envelope1Phase=4;
    startingValueRelease1 = sustainValueCh1*sustainMultiplier;
    rampDuration1 = releaseValueCh1 * release1Multiplier;
    startTime1 = millis();
  } 

  //3. See if the loop is ended? Do nothing if it is not ended.
  if ((nLoop1Count<nLoopLengthCh1) || (nLoopLengthCh1==0 && gate1Active==1)) {
    //3a. the nLoop is not finished. Do nothing? Let the above do its thing, adding a n or for nLoop1Active=no
    //DOES BELOW INSTEAD.
  } else  {
    //Serial.println("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
    //ALRIGHT! FOR NDECAY TO WORK IN LENGTH=0 WE NEED ANOTHER SECTION...?
    //4a. The nLoops are finished, wait for the gate to be released and then set the nLoopCount to 0.
    if (gate1Active==1) {
      //do nothing
    } else {
      nLoop1Count=0;

      //MOVED IN HERE TO SEE IF THAT WORKS
      //SEEMS TO WORK SOMETIMES, if you hold the gate until the nloops are finished... otherwise no. it runs irt one more time setting it one decay lower...
      nLoop1Active=0;
      //maxValue=originalMaxValue;
      //sustainMultiplier=originalSustainMultiplier;
      
      //WAIT! This could be the reason the last loop is in max... Instead do this in the phase==40 and nLoop1Active==0
      //REMOVED IT COMMPLETELY HERE AND JUST DO IT IN THE ENVELOPWRITE...
      //maxValueCh1=maxValue;
      //sustainMultiplierCh1=sustainMultiplier;
    }
  }
}


void envelopeStartnLoop2() {
  //1. Wait for gate on.
  if (gate2Active==1)  { // || nLoop1Active==1
    //2. Activate the loop. Making sure we only activate the loop no counting now... And only start it if there are loops left in nLoop, OR if nLoopLengthChX is 0.
    if ((nLoop2Active==0 && nLoop2Count<nLoopLengthCh2) || nLoopLengthCh2==0) {
      nLoop2Active=1;
    }
  }
  if (nLoop2Active==1 && (nLoop2Count<=nLoopLengthCh2 || nLoopLengthCh2==0)) {
    if (envelope2Phase==0) {
      //2. Count the loop. DO THIS IN 40 instead!
      nLoop2Count++;
      //Start the envelope.
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
  
  if (nLoop2Count<nLoopLengthCh2) {
    //do nothing? Let the above do its thing, adding an or for nLoop1Active
  } else  {
    nLoop2Active=0;
    if (gate2Active==1) {
      //do nothing
    } else {
      nLoop2Count=0;
    }
  }
}
