

void writeEeprom(int section) {
  //or press button to save config.
  //int eepromStartAddress=0; //SET IN CONFIG.
  
  //int addAddress = 0;  // EEPROM address to store data
  //int sensorValue = analogRead(A0);  // Read analog pin A0

  //EEPROM.put(address, sensorValue);  // Store the analog value
  //EEPROM.put(address+2, sensorValue);  // Store the analog value
  //EEPROM.put(address+addAddress, sensorValue);  // Store the analog value
  //EEPROM.update()

  /*
   * startadress should be the first position in eeprom, next should be a counter? then variables below
   * channelselect 1 SKIP!?
   * 
   * SECTION 1 ADSR1 values.
   * unsigned int attackValueCh1; 2bytes
   * unsigned int decayValueCh1; 2bytes
   * unsigned int sustainValueCh1; 2bytes
   * unsigned int releaseValueCh1; 2bytes
   */
   //if (section == 0) {
    EEPROM.put(eepromStartAddress, 512);
    EEPROM.put(eepromStartAddress+2, 512);
    EEPROM.put(eepromStartAddress+4, 512);
    EEPROM.put(eepromStartAddress+6, 512);
   //}
   //if (section == 1) {
    EEPROM.put(eepromStartAddress+8, 512);
    EEPROM.put(eepromStartAddress+10, 512);
    EEPROM.put(eepromStartAddress+12, 512);
    EEPROM.put(eepromStartAddress+14, 512);
   //}

   //if (section == 2) {
   //Length Multipliers
   EEPROM.put(eepromStartAddress+16, 1);
   EEPROM.put(eepromStartAddress+17, 1);
   EEPROM.put(eepromStartAddress+18, 1);

   EEPROM.put(eepromStartAddress+19, 1);
   EEPROM.put(eepromStartAddress+20, 1);
   EEPROM.put(eepromStartAddress+21, 1);
   //Slopes
   EEPROM.put(eepromStartAddress+22, 1.0); //float=4bytes
   EEPROM.put(eepromStartAddress+26, 1.0); //float=4bytes
   EEPROM.put(eepromStartAddress+30, 1.0); //float=4bytes
   EEPROM.put(eepromStartAddress+34, 1.0); //float=4bytes
   EEPROM.put(eepromStartAddress+38, 1.0); //float=4bytes
   EEPROM.put(eepromStartAddress+42, 1.0); //float=4bytes

   //MODEs and ACTing
   EEPROM.put(eepromStartAddress+46, 1); //1 byte
   EEPROM.put(eepromStartAddress+47, 1); //1 byte

   EEPROM.put(eepromStartAddress+48, 0); //1 byte
   EEPROM.put(eepromStartAddress+49, 0); //1 bytes, which if any parameter the CV input should control.

   EEPROM.put(eepromStartAddress+50, 0); //1 bytes, 
   EEPROM.put(eepromStartAddress+51, 0); //1 bytes, 

   EEPROM.put(eepromStartAddress+52, 0); //1 bytes, 
   EEPROM.put(eepromStartAddress+53, 0); //1 bytes, 
   
   //nLoopCh1, nLoopCh2,
   //byte nLoopLengthCh1, nLoopLengthCh2;
   //modulemode
   
  
}
