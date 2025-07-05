//const int potPin = A0;          // Analog pin connected to the potentiometer
//bool caughtValue = 0;            // The saved "caught" potentiometer value
//bool wentAbove = false;         // Flag to track if the value went above the saved value
//bool wentBelow = false;         // Flag to track if the value went below the saved value

void releasePots() {
  wentAboveBelow=0;
  potsCaught=0;
  if (channelSelect && !menuSelected) {
    //When changing channel from ch2 to ch1 set the potValues to be catched for Ch1.
    attackPotValue=attackValueCh1;
    decayPotValue=decayValueCh1;
    sustainPotValue=sustainValueCh1;
    releasePotValue=releaseValueCh1;
  } else if (!channelSelect && !menuSelected) {
    //When changing channel from ch1 to ch2 set the potValues to be catched for Ch2.
    attackPotValue=attackValueCh2;
    decayPotValue=decayValueCh2;
    sustainPotValue=sustainValueCh2;
    releasePotValue=releaseValueCh2;
  } else if (menuSelected) { //else for menus etc... Channel 1
    //NEEDS TO BE DONE FOR EACH MENU!!!!
    if (activeButton==1) { //Exponential curve
      //When going into menu1, set the PotValues to the exponent of the channel.
      if (!channelSelect) {
        attackPotValue=menuA1Exp;
        decayPotValue=menuD1Exp;
        sustainPotValue=0;
        releasePotValue=menuR1Exp;
      } else {
        attackPotValue=menuA2Exp;
        decayPotValue=menuD2Exp;
        sustainPotValue=0;
        releasePotValue=menuR2Exp;
      }
    }    
    if (activeButton==2) { //envelope lengths
      if (!channelSelect) {
        attackPotValue=menuA1Multiplier;
        decayPotValue=menuD1Multiplier;
        sustainPotValue=0;
        releasePotValue=menuR1Multiplier;
      } else {
        attackPotValue=menuA2Multiplier;
        decayPotValue=menuD2Multiplier;
        sustainPotValue=0;
        releasePotValue=menuR2Multiplier;
      }
    }
    if (activeButton==3) { //envelope lengths
        attackPotValue=menu1Mode;
    }
    if (activeButton==4) { //func-menu
      if (!channelSelect) {
        attackPotValue=menuA1CV;
        decayPotValue=menuD1nDecay;
        sustainPotValue=menuS1EndOf;
        releasePotValue=menuR1nLoop;
      }
    }
    
  }
}

void releasePotsFromMenu() { 
  //THIS ONE NEEDS TO BE DIFFERENT
  //Because releasePots is when changing between the channels, and then the opposite value should be set. 
  //In the case of the menu you get back into the same channel you were, so you need to get that value again and not the opposite...
  wentAboveBelow=0;
  potsCaught=0;
  if (!channelSelect && !menuSelected) { //THIS LINE CHANGED from channelSelect to !channelSelect
    attackPotValue=attackValueCh1;
    decayPotValue=decayValueCh1;
    sustainPotValue=sustainValueCh1;
    releasePotValue=releaseValueCh1;
  } else if (channelSelect && !menuSelected) { //THIS LINE CHANGED from !channelSelect to channelSelect
    attackPotValue=attackValueCh2;
    decayPotValue=decayValueCh2;
    sustainPotValue=sustainValueCh2;
    releasePotValue=releaseValueCh2;
  } else if (menuSelected) { //else for menus etc...
    //shouldnt have to do anything here...
  }
}

void catchPots() {
  //if (catchPotsTimer>100) {
    //catchPotsTimer=0;
    //do for each pot.
    //int potValue = analogRead(attackPot);  // Read the current potentiometer value
    /* The byte: wentAboveBelow is 8 bits, first four bits are set adsr if the pot has gone above the actual value, and the four last bits if the pot has gone below the actual value.
     * The byte: potsCaught is using the first four bits to set/check which pots are catched. 
     * Both these need to be zeroed every time we change to a function or change the channel.
     * Within this function we also set the values of the pots depending on channelselect and menu...
     */
    //ATTACKPOTENTIOMETER
    attackPotRead=analogRead(attackPot);
    
    if (!isBitSet(potsCaught,0)) { //attackPot is not catched, lets catch it.
      //attackPotRead=analogRead(attackPot);
      if (attackPotRead >= attackPotValue) { setBitHigh(wentAboveBelow,0); // Mark that the value has gone higher
      }
      if (attackPotRead <= attackPotValue) { setBitHigh(wentAboveBelow,4); // Mark that the value has gone lower
      }
    }
    if (isBitSet(wentAboveBelow,0) && isBitSet(wentAboveBelow,4)) { //it is now catched, now lets get the value to the attackPotValue;
      setBitHigh(potsCaught,0); //ATTACK is caught
      //attackPotValue = analogRead(attackPot);     // Save the new caught value    
      attackPotValue = attackPotRead;     // Save the new caught value    
    }
  
    //DECAYPOTENTIOMETER
     decayPotRead=analogRead(decayPot);
     
    if (decayPotRead >= decayPotValue) {
      setBitHigh(wentAboveBelow,1);           // Mark that the value has gone higher
    }
    if (decayPotRead <= decayPotValue) {
      //wentBelow = true;           // Mark that the value has gone lower
      setBitHigh(wentAboveBelow,5);
    }
    if (isBitSet(wentAboveBelow,1) && isBitSet(wentAboveBelow,5)) {
      setBitHigh(potsCaught,1); //DECAY is caught
      //decayPotValue = analogRead(decayPot);     // Save the new caught value    
      decayPotValue = decayPotRead;     // Save the new caught value    
    }
  
    //SUSTAINPOTENTIOMETER
    sustainPotRead=analogRead(sustainPot);
    
    if (sustainPotRead >= sustainPotValue) {
      setBitHigh(wentAboveBelow,2);           // Mark that the value has gone higher
    }
    if (sustainPotRead <= sustainPotValue) {
      //wentBelow = true;           // Mark that the value has gone lower
      setBitHigh(wentAboveBelow,6);
    }
    if (isBitSet(wentAboveBelow,2) && isBitSet(wentAboveBelow,6)) {
      setBitHigh(potsCaught,2); //SUSTAIN is caught
      //sustainPotValue = analogRead(sustainPot);     // Save the new caught value    
      sustainPotValue = sustainPotRead;     // Save the new caught value    
    }
  
    //RELEASEPOTENTIOMETER
    //releasePotRead=analogRead(releasePot);
    //releasePotReadOld = releasePotRead; //Save the old Value.
    releasePotRead=analogRead(releasePot);
    //if (releasePotReadOld>=releasePotRead+4) { lastPotTurned=4; }
    //if (releasePotReadOld<=releasePotRead-4) { lastPotTurned=4; }
    
    if (releasePotRead >= releasePotValue) {
      setBitHigh(wentAboveBelow,3);           // Mark that the value has gone higher
    }
    if (releasePotRead <= releasePotValue) {
      //wentBelow = true;           // Mark that the value has gone lower
      setBitHigh(wentAboveBelow,7);
    }
    if (isBitSet(wentAboveBelow,3) && isBitSet(wentAboveBelow,7)) {
      setBitHigh(potsCaught,3); //RELEASE is caught
      //releasePotValue = analogRead(releasePot);     // Save the new caught value    
      releasePotValue = releasePotRead;     // Save the new caught value    
    }
  //}
  //catchPotsTimer=+;

  
  //Channel 1 is selected, no menu is selected
  if (!channelSelect && !menuSelected) {
    if (isBitSet(potsCaught,0)) { attackValueCh1=attackPotValue; }
    if (isBitSet(potsCaught,1)) { decayValueCh1=decayPotValue; }
    if (isBitSet(potsCaught,2)) { sustainValueCh1=sustainPotValue; }
    if (isBitSet(potsCaught,3)) { releaseValueCh1=releasePotValue; }
  }
  if (channelSelect && !menuSelected) {
    if (isBitSet(potsCaught,0)) { attackValueCh2=attackPotValue; }
    if (isBitSet(potsCaught,1)) { decayValueCh2=decayPotValue; }
    if (isBitSet(potsCaught,2)) { sustainValueCh2=sustainPotValue; }
    if (isBitSet(potsCaught,3)) { releaseValueCh2=releasePotValue; }
  }
  if (menuSelected) { 
    //just use the ADSR PotValues....
  }

  /* Below added to take into account that the Input gate 2 can be used as a CV source, controlling either nothing, A, D, S, or R, and either positive or negative effect on the knob value.
   * Could maybe do with its own function? Or part of the catchpots still because they are quite intertwinced.
   * MAybe just do it once every 50 cycles?
   */
   if (CVcontrolCount=50) {
    CVcontrolCount=0;
    switch (CVcontrol) {
      case 0: 
        //Control nothing do nothing
        CVcontrolValue=0;
        break;
      case 1:
        //Control the Attack, a value between the value of the pot, and the value of the incoming signal ALSO positive or negative modulation... done with more cases.
        CVcontrolValue=analogRead(CVinput);
        //attackValueCh1=map(CVcontrolValue,1023,0,attackValueCh1,1023); //or just limit the lower voltage? WE NEED TO SWITCH THIS AROUND BECAUSE IT IS NOT INVERTED ANYMORE!
        attackValueCh1wCV=map(CVcontrolValue,0,1023,attackValueCh1,1023); //or just limit the lower voltage? WE NEED TO SWITCH THIS AROUND BECAUSE IT IS NOT INVERTED ANYMORE!
        break;
      case 2:
        //Control the Decay
        CVcontrolValue=analogRead(CVinput);
        decayValueCh1wCV=map(CVcontrolValue,0,1023,decayValueCh1,1023); //or just limit the lower voltage?
        //decayValueCh1=CVcontrolValue;
        break;
      case 3:
        //Control the Sustain
        CVcontrolValue=analogRead(CVinput);
        sustainValueCh1wCV=map(CVcontrolValue,0,1023,sustainValueCh1,1023); //or just limit the lower voltage?
        break;
      case 4:
        //Control the Release
        CVcontrolValue=analogRead(CVinput);
        releaseValueCh1wCV=map(CVcontrolValue,0,1023,releaseValueCh1,1023); //or just limit the lower voltage?
        break;
      //Again, add 5-8 for negative modulation...
      case 5:
        //Control the Attack, a value between the value of the pot, and the value of the incoming signal ALSO positive or negative modulation... done with more cases.
        CVcontrolValue=analogRead(CVinput);
        attackValueCh1wCV=map(CVcontrolValue,0,1023,0,attackValueCh1); //or just limit the lower voltage?
        break;
      case 6:
        //Control the Decay
        CVcontrolValue=analogRead(CVinput);
        decayValueCh1wCV=map(CVcontrolValue,0,1023,0,decayValueCh1); //or just limit the lower voltage?
        //decayValueCh1=CVcontrolValue;
        break;
      case 7:
        //Control the Sustain
        CVcontrolValue=analogRead(CVinput);
        sustainValueCh1wCV=map(CVcontrolValue,0,1023,0,sustainValueCh1); //or just limit the lower voltage?
        break;
      case 8:
        //Control the Release
        CVcontrolValue=analogRead(CVinput);
        releaseValueCh1wCV=map(CVcontrolValue,0,1023,0,releaseValueCh1); //or just limit the lower voltage?
        break;
     } 
   } else { CVcontrolCount++; }
   
}
