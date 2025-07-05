// Function to check button states
void checkButton(int buttonID, int pin, bool &lastState, unsigned long &pressTime) {
    bool currentState = digitalRead(pin);
    if (currentState == HIGH && lastState == LOW) { // Button just pressed
        pressTime = millis(); // Record press time
    }
    if (currentState == HIGH) { // Button is being held
        if (!menuSelected && (millis() - pressTime >= menuHoldTime)) {
            enterMenu(buttonID); // Enter menu mode
        }
    }
    if (currentState == LOW && lastState == HIGH) { // Button released
        if (!menuSelected) {
            if (buttonID == 1) shortPress1();
            if (buttonID == 2) shortPress2();
            if (buttonID == 3) shortPress3();
            if (buttonID == 4) shortPress4();
        } else {
            exitMenu(); // Exit menu mode when button is released
        }
    }
    lastState = currentState; // Update last state
}

// Short press actions
void shortPress1() {
    //CHANGE CHANNEL
    releasePots(); //changing channel means the pots needs to be released.
    channelSelect=!channelSelect;
    if (channelSelect) { setLeds(1,1,1,1); setLedColor(0); } else { setLeds(1,1,1,1); setLedColor(1); }
    ledStartTime=millis();
    ledTimeout=200;
}

void shortPress2() {
    //LOOP
    /* Previously Loop, now "Act", how a channel should act on a gate or trig, 
     * either as a 
     * GATE (1) which is normal ADSR, 
     * TRIG (2) which is a "oneshot" where the whole ADSR is run once, with no sustain.
     * LOOP,(3) where the whole ADSR is looped, with no sustain. if sustain and release is 0 then it will be a AD-loop.
     * One 4th act could be to loop while gate is held. then light up gate and loop.
     */
     
    if (!channelSelect) {
      //CHannel 1
      if (actCh1==0) {
        //It is GATE
        actCh1=1; //Set it to TRIG
        setLeds(0,1,0,0); setLedColor(1);
      } else if (actCh1==1) {
        //It is TRIG
        actCh1=2; //Set it to LOOP
        setLeds(0,0,1,0); setLedColor(1);  
      } else if (actCh1==2) {
         //It is LOOP
        actCh1=3; //Set it to nLOOP
        setLeds(0,0,0,1); setLedColor(1);
      } else {
         //It is nLOOP
        actCh1=0; //Set it to GATE
        setLeds(1,0,0,0); setLedColor(1);
      }
    } else {
      //Channel2
      if (actCh2==0) {
        //It is GATE
        actCh2=1; //Set it to TRIG
        setLeds(0,1,0,0); setLedColor(0);
      } else if (actCh2==1) {
        //It is TRIG
        actCh2=2; //Set it to LOOP
        setLeds(0,0,1,0); setLedColor(0);
      } else if (actCh2==2) {
         //It is LOOP
        actCh2=3; //Set it to nLOOP
        setLeds(0,0,0,1); setLedColor(0);
      } else {
         //It is nLOOP
        actCh2=0; //Set it to GATE
        setLeds(1,0,0,0); setLedColor(0);
      }
    }
    ledStartTime=millis();
    ledTimeout=200;
}

void shortPress3() {
    //FLYTTA LOAD HIT SÅ FÅR VI EN MENY LEDIG TILL ATT STARTA A D S OCH Rs, ELLER HA KVAR SOM PUSH FÖR ATT ÄNDRA MELLAN ADVANCE SLOPE OCH VANLIG?
    //ELLER Det som gäller nu, functions, ex. nLoop n's och EndOf.
    //LOAD saved parameters.
    readEeprom(1);
    setLeds(0,0,0,1); setLedColor(1); //1=green
    ledStartTime=millis();
    ledTimeout=200;
    //exitMenu();
    
}

void shortPress4() {
    //SAVE!
    writeEeprom(1);
    setLeds(0,0,0,1); setLedColor(0); //0=red
    ledStartTime=millis();
    ledTimeout=200;
}

// Enter menu mode
void enterMenu(int buttonID) {
    menuSelected = true;
    activeButton = buttonID;
    
    releasePots();
}

// Exit menu mode
void exitMenu() {
  setLeds(0,0,0,0);
  menuSelected = false;
  releasePotsFromMenu();
  activeButton = 0;
}

// Update menu based on active button
void updateMenu() {
    if (activeButton == 1) menu1();
    if (activeButton == 2) menu2();
    if (activeButton == 3) menu3();
    if (activeButton == 4) menu4();
}

// Menu functions
