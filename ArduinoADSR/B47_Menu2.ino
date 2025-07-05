void menu2() {
  //SET ENVELOPE LENGTHS
  if (!channelSelect) { //CHANNEL1
    menuA1Multiplier=attackPotValue;
    menuD1Multiplier=decayPotValue;
    menuR1Multiplier=releasePotValue;
    
    if (menuA1Multiplier<=341) { attack1Multiplier=envelopeMultiplier0; menuLedColor1=0; }
    else if (menuA1Multiplier<=682) { attack1Multiplier=envelopeMultiplier1; menuLedColor1=2; }
    else { attack1Multiplier=envelopeMultiplier2;  menuLedColor1=1;}

    if (menuD1Multiplier<=341) { decay1Multiplier=envelopeMultiplier0; menuLedColor2=0; }
    else if (menuD1Multiplier<=682) { decay1Multiplier=envelopeMultiplier1; menuLedColor2=2; }
    else { decay1Multiplier=envelopeMultiplier2;  menuLedColor2=1;}

    if (menuR1Multiplier<=341) { release1Multiplier=envelopeMultiplier0; menuLedColor4=0; }
    else if (menuR1Multiplier<=682) { release1Multiplier=envelopeMultiplier1; menuLedColor4=2; }
    else { release1Multiplier=envelopeMultiplier2;  menuLedColor4=1;}

  } else if (channelSelect) { //CHANNEL 2
    menuA2Multiplier=attackPotValue;
    menuD2Multiplier=decayPotValue;
    menuR2Multiplier=releasePotValue;
    
    if (menuA2Multiplier<=341) { attack2Multiplier=envelopeMultiplier0; menuLedColor1=0; }
    else if (menuA2Multiplier<=682) { attack2Multiplier=envelopeMultiplier1; menuLedColor1=2; }
    else { attack2Multiplier=envelopeMultiplier2;  menuLedColor1=1;}

    if (menuD2Multiplier<=341) { decay2Multiplier=envelopeMultiplier0; menuLedColor2=0; }
    else if (menuD2Multiplier<=682) { decay2Multiplier=envelopeMultiplier1; menuLedColor2=2; }
    else { decay2Multiplier=envelopeMultiplier2;  menuLedColor2=1;}

    if (menuR2Multiplier<=341) { release2Multiplier=envelopeMultiplier0; menuLedColor4=0; }
    else if (menuR2Multiplier<=682) { release2Multiplier=envelopeMultiplier1; menuLedColor4=2; }
    else { release2Multiplier=envelopeMultiplier2;  menuLedColor4=1;}
  }
  menuLeds(menuLedColor1,menuLedColor2,3,menuLedColor4);
}
