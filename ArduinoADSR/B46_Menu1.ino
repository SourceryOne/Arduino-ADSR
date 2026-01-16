void menu1() {
  //SET ENVELOPE Exponential curves per section.
  if (!channelSelect) { //CHANNEL1
    menuA1Exp=attackPotValue;
    menuD1Exp=decayPotValue;
    menuR1Exp=releasePotValue;

    if (advancedExponent) {
      if (menuA1Exp<=500) {
        attack1Exponent = 0.5 + (menuA1Exp * (0.5 / 500.0));  // Maps 0-512 to 0.5-1.0
        menuLedColor1=0;
      } else if (menuA1Exp>=524) {
        attack1Exponent = 1.0 + ((menuA1Exp - 524) * (2.5 / (1023 - 524)));  // Maps 525-1023 to 1.0-3.5
        menuLedColor1=1;
      } else {
        attack1Exponent=1.0; 
        menuLedColor1=2;
      }
// Somehow this seems to be inverted? Maybe because they are negative?       
      if (menuD1Exp<=500) {
        decay1Exponent = 1.0 + ((500.0 - menuD1Exp) * (2.5 / 500.0));
        menuLedColor2=0;
      } else if (menuD1Exp>=524) {
        decay1Exponent = 0.5 + ((1023 - menuD1Exp) * (0.5 / (1023.0 - 524.0))); 
        menuLedColor2=1;
      } else {
        decay1Exponent=1.0; 
        menuLedColor2=2;
      }
      if (menuR1Exp<=500) {
        release1Exponent = 1.0 + ((500.0 - menuR1Exp) * (2.5 / 500.0));
        menuLedColor4=0;
      } else if (menuR1Exp>=524) {
        release1Exponent = 0.5 + ((1023 - menuR1Exp) * (0.5 / (1023 - 524)));  // Maps 525-1023 to 1.0-3.5
        menuLedColor4=1;
      } else {
        release1Exponent=1.0; 
        menuLedColor4=2;
      }
      //
    } else {
      if (menuA1Exp<=341) { attack1Exponent=envelopeExponent0; menuLedColor1=0; } //fast start, slow finish. GREEN LED
      else if (menuA1Exp<=682) { attack1Exponent=envelopeExponent1; menuLedColor1=2; } //linear NO LED
      else { attack1Exponent=envelopeExponent2;  menuLedColor1=1;} //slow start, fast finish RED LED
  
      if (menuD1Exp<=341) { decay1Exponent=envelopeExponent0; menuLedColor2=0; }
      else if (menuD1Exp<=682) { decay1Exponent=envelopeExponent1; menuLedColor2=2; }
      else { decay1Exponent=envelopeExponent1;  menuLedColor2=1;}
  
      if (menuR1Exp<=341) { release1Exponent=envelopeExponent0; menuLedColor4=0; }
      else if (menuR1Exp<=682) { release1Exponent=envelopeExponent1; menuLedColor4=2; }
      else { release1Exponent=envelopeExponent2;  menuLedColor4=1;}
    }



    
  } else if (channelSelect) { //CHANNEL 2
    menuA2Exp=attackPotValue;
    menuD2Exp=decayPotValue;
    menuR2Exp=releasePotValue;
    
    if (advancedExponent) {
      if (menuA2Exp<=500) {
        attack2Exponent = 0.5 + (menuA2Exp * (0.5 / 500.0));  // Maps 0-512 to 0.5-1.0
        menuLedColor1=0;
      } else if (menuA2Exp>=524) {
        attack2Exponent = 1.0 + ((menuA2Exp - 524) * (2.5 / (1023 - 524)));  // Maps 525-1023 to 1.0-3.5
        menuLedColor1=1;
      } else {
        attack2Exponent=1.0; 
        menuLedColor1=2;
      }
      if (menuD2Exp<=500) {
        //decay2Exponent = 0.5 + (menuD2Exp * (0.5 / 500.0));  // Maps 0-512 to 0.5-1.0
        decay2Exponent = 1.0 + ((500.0 - menuD2Exp) * (2.5 / 500.0));
        menuLedColor2=0;
      } else if (menuD2Exp>=524) {
        //decay2Exponent = 1.0 + ((menuD2Exp - 524) * (2.5 / (1023 - 524)));  // Maps 525-1023 to 1.0-3.5
        decay2Exponent = 0.5 + ((1023 - menuD2Exp) * (0.5 / (1023.0 - 524.0))); 
        menuLedColor2=1;
      } else {
        decay2Exponent=1.0; 
        menuLedColor2=2;
      }
      if (menuR2Exp<=500) {
        //release2Exponent = 0.5 + (menuR2Exp * (0.5 / 500.0));  // Maps 0-512 to 0.5-1.0
        release2Exponent = 1.0 + ((500.0 - menuR2Exp) * (2.5 / 500.0));
        menuLedColor4=0;
      } else if (menuD2Exp>=524) {
        //release2Exponent = 1.0 + ((menuR2Exp - 524) * (2.5 / (1023 - 524)));  // Maps 525-1023 to 1.0-3.5
        release2Exponent = 0.5 + ((1023 - menuR2Exp) * (0.5 / (1023 - 524)));  // Maps 525-1023 to 1.0-3.5
        menuLedColor4=1;
      } else {
        release2Exponent=1.0; 
        menuLedColor4=2;
      }
    } else {
      if (menuA2Exp<=341) { attack2Exponent=envelopeExponent0; menuLedColor1=0; } //fast start, slow finish. GREEN LED
      else if (menuA2Exp<=682) { attack2Exponent=envelopeExponent1; menuLedColor1=2; } //linear NO LED
      else { attack2Exponent=envelopeExponent2;  menuLedColor1=1;} //slow start, fast finish RED LED
  
      if (menuD2Exp<=341) { decay2Exponent=envelopeExponent0; menuLedColor2=0; }
      else if (menuD2Exp<=682) { decay2Exponent=envelopeExponent1; menuLedColor2=2; }
      else { decay2Exponent=envelopeExponent1;  menuLedColor2=1;}
  
      if (menuR2Exp<=341) { release2Exponent=envelopeExponent0; menuLedColor4=0; }
      else if (menuR2Exp<=682) { release2Exponent=envelopeExponent1; menuLedColor4=2; }
      else { release2Exponent=envelopeExponent2;  menuLedColor4=1;}
    }
  }
  menuLeds(menuLedColor1,menuLedColor2,3,menuLedColor4);
}
