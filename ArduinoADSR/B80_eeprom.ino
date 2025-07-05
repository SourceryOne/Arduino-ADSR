

void writeEeprom(int section) {
  /*
   * startadress should be the first position in eeprom, next should be a counter? then variables below
   * channelselect 1 SKIP!?
   */
   EEPROM.put(eepromStartAddress, attackValueCh1);
   EEPROM.put(eepromStartAddress+2, decayValueCh1);
   EEPROM.put(eepromStartAddress+4, sustainValueCh1);
   EEPROM.put(eepromStartAddress+6, releaseValueCh1);
   EEPROM.put(eepromStartAddress+8, attackValueCh2);
   EEPROM.put(eepromStartAddress+10, decayValueCh2);
   EEPROM.put(eepromStartAddress+12, sustainValueCh2);
   EEPROM.put(eepromStartAddress+14, releaseValueCh2);
   EEPROM.put(eepromStartAddress+16, attack1Multiplier);
   EEPROM.put(eepromStartAddress+17, decay1Multiplier);
   EEPROM.put(eepromStartAddress+18, release1Multiplier);
   EEPROM.put(eepromStartAddress+19, attack2Multiplier);
   EEPROM.put(eepromStartAddress+20, decay2Multiplier);
   EEPROM.put(eepromStartAddress+21, release2Multiplier);
   EEPROM.put(eepromStartAddress+22, attack1Exponent); //float=4bytes
   EEPROM.put(eepromStartAddress+26, decay1Exponent); //float=4bytes
   EEPROM.put(eepromStartAddress+30, release1Exponent); //float=4bytes
   EEPROM.put(eepromStartAddress+34, attack2Exponent); //float=4bytes
   EEPROM.put(eepromStartAddress+38, decay2Exponent); //float=4bytes
   EEPROM.put(eepromStartAddress+42, release2Exponent); //float=4bytes

   //MODEs and ACTing
   EEPROM.put(eepromStartAddress+46, actCh1); //1 byte
   EEPROM.put(eepromStartAddress+47, actCh2); //1 byte

   EEPROM.put(eepromStartAddress+48, EndOfCh1); //1 byte
   EEPROM.put(eepromStartAddress+49, CVcontrol); //1 bytes, which if any parameter the CV input should control.

   EEPROM.put(eepromStartAddress+50, nLoopLengthCh1); //1 bytes, 
   EEPROM.put(eepromStartAddress+51, nLoopLengthCh2); //1 bytes, 

   EEPROM.put(eepromStartAddress+52, nLoopDecayCh1); //1 bytes, 
   EEPROM.put(eepromStartAddress+53, nLoopDecayCh2); //1 bytes, 
   
   //EEPROM.put(eepromStartAddress+54, moduleMode); //1 bytes, 



   
  
}

void readEeprom(int section) {
    EEPROM.get(eepromStartAddress, attackValueCh1);  // Read the stored analog value
    EEPROM.get(eepromStartAddress+2, decayValueCh1);  // Read the stored analog value
    EEPROM.get(eepromStartAddress+4, sustainValueCh1);  // Read the stored analog value 
    EEPROM.get(eepromStartAddress+6, releaseValueCh1);  // Read the stored analog value 
    EEPROM.get(eepromStartAddress+8, attackValueCh2);  // Read the stored analog value
    EEPROM.get(eepromStartAddress+10, decayValueCh2);  // Read the stored analog value
    EEPROM.get(eepromStartAddress+12, sustainValueCh2);  // Read the stored analog value 
    EEPROM.get(eepromStartAddress+14, releaseValueCh2);  // Read the stored analog value 

  //Also needs to set the PotValues when loading so they need to be catched again.
  releasePotsFromMenu();
/*  wentAboveBelow=0;
  potsCaught=0;
  if (channelSelect) {
    attackPotValue=attackValueCh1;
    decayPotValue=decayValueCh1;
    sustainPotValue=sustainValueCh1;
    releasePotValue=releaseValueCh1;
  } else if (!channelSelect) {
    attackPotValue=attackValueCh2;
    decayPotValue=decayValueCh2;
    sustainPotValue=sustainValueCh2;
    releasePotValue=releaseValueCh2;
  }
  */
   
   //Length Multipliers
   EEPROM.get(eepromStartAddress+16, attack1Multiplier);
   EEPROM.get(eepromStartAddress+17, decay1Multiplier);
   EEPROM.get(eepromStartAddress+18, release1Multiplier);
   //approximating values for the menu.
   if (attack1Multiplier==envelopeMultiplier0) { menuA1Multiplier=0; } else if (attack1Multiplier==envelopeMultiplier2) { menuA1Multiplier=1023; } else { menuA1Multiplier=512; }
   if (decay1Multiplier==envelopeMultiplier0) { menuD1Multiplier=0; } else if (decay1Multiplier==envelopeMultiplier2) { menuD1Multiplier=1023; } else { menuD1Multiplier=512; }
   if (release1Multiplier==envelopeMultiplier0) { menuR1Multiplier=0; } else if (release1Multiplier==envelopeMultiplier2) { menuR1Multiplier=1023; } else { menuR1Multiplier=512; }
   
   EEPROM.get(eepromStartAddress+19, attack2Multiplier);
   EEPROM.get(eepromStartAddress+20, decay2Multiplier);
   EEPROM.get(eepromStartAddress+21, release2Multiplier);
   //approximating values for the menu.
   if (attack2Multiplier==envelopeMultiplier0) { menuA2Multiplier=0; } else if (attack2Multiplier==envelopeMultiplier2) { menuA2Multiplier=1023; } else { menuA2Multiplier=512; }
   if (decay2Multiplier==envelopeMultiplier0) { menuD2Multiplier=0; } else if (decay2Multiplier==envelopeMultiplier2) { menuD2Multiplier=1023; } else { menuD2Multiplier=512; }
   if (release2Multiplier==envelopeMultiplier0) { menuR2Multiplier=0; } else if (release2Multiplier==envelopeMultiplier2) { menuR2Multiplier=1023; } else { menuR2Multiplier=512; }

   
   //Slopes
   EEPROM.get(eepromStartAddress+22, attack1Exponent);
   EEPROM.get(eepromStartAddress+26, decay1Exponent);
   EEPROM.get(eepromStartAddress+30, release1Exponent);
   //aproximating the value for the menus.
   if (attack1Exponent<1.0) { menuA1Exp=0; } else if (attack1Exponent>1.0) { menuA1Exp=1023; } else { menuA1Exp=512; }
   if (decay1Exponent<1.0) { menuD1Exp=0; } else if (decay1Exponent>1.0) { menuD1Exp=1023; } else { menuD1Exp=512; }
   if (release1Exponent<1.0) { menuR1Exp=0; } else if (release1Exponent>1.0) { menuR1Exp=1023; } else { menuR1Exp=512; }

   EEPROM.get(eepromStartAddress+34, attack2Exponent);
   EEPROM.get(eepromStartAddress+38, decay2Exponent);
   EEPROM.get(eepromStartAddress+42, release2Exponent); //float=4bytes
   //aproximating the value for the menus.
   if (attack2Exponent<1.0) { menuA2Exp=0; } else if (attack2Exponent>1.0) { menuA2Exp=1023; } else { menuA2Exp=512; }
   if (decay2Exponent<1.0) { menuD2Exp=0; } else if (decay2Exponent>1.0) { menuD2Exp=1023; } else { menuD2Exp=512; }
   if (release2Exponent<1.0) { menuR2Exp=0; } else if (release2Exponent>1.0) { menuR2Exp=1023; } else { menuR2Exp=512; }

   //MODEs and ACTing
   EEPROM.get(eepromStartAddress+46, actCh1); //1 byte
   EEPROM.get(eepromStartAddress+47, actCh2); //1 byte
   
   EEPROM.get(eepromStartAddress+48, EndOfCh1); //1 byte
   EEPROM.get(eepromStartAddress+49, CVcontrol); //1 bytes, which if any parameter the CV input should control.
   
   EEPROM.get(eepromStartAddress+50, nLoopLengthCh1); //1 bytes, 
   EEPROM.get(eepromStartAddress+51, nLoopLengthCh2); //1 bytes, 

   EEPROM.get(eepromStartAddress+52, nLoopDecayCh1); //1 bytes, 
   EEPROM.get(eepromStartAddress+53, nLoopDecayCh2); //1 bytes, 
 
   //EEPROM.get(eepromStartAddress+54, moduleMode); //1 bytes,

//Use EEPROM.put() for multi-byte values (e.g., int, float).
// Use EEPROM.update() instead of write() to prevent unnecessary EEPROM wear.
// Analog values range from 0-1023 (fits in 2 bytes).
// EEPROM has a write limit (~100,000 cycles per address) → Minimize writes!
}
