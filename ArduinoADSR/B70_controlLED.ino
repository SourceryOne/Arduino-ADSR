void controlLeds() {
  if (ledStartTime>0) { //turn of any leds that is running from eg. menus and stuff.
    if (millis()-ledStartTime>200) { setLeds(0,0,0,0); ledStartTime=0; }
  } else {
    if (!channelSelect && !menuSelected) { //channel 1 no menu.
      analogWrite(redPWM,0);
      if (envelope1Phase==0) { setLeds(0,0,0,0); } //OCR0A should be green
      if (envelope1Phase==1) { setLeds(1,0,0,0); analogWrite(greenPWM,map(currentValue1,0,maxValue,0,254)); }
      if (envelope1Phase==2) { setLeds(0,1,0,0); analogWrite(greenPWM,map(currentValue1,0,maxValue,0,254)); }
      if (envelope1Phase==3) { setLeds(0,0,1,0); analogWrite(greenPWM,map(currentValue1,0,maxValue,0,254)); }
      if (envelope1Phase==4) { setLeds(0,0,0,1); analogWrite(greenPWM,map(currentValue1,0,maxValue,0,254)); }      
    } else if (channelSelect && !menuSelected) { //channel 2 no menu.
      analogWrite(greenPWM,0);
      if (envelope2Phase==0) { setLeds(0,0,0,0); } //OCR0B should be red.
      if (envelope2Phase==1) { setLeds(1,0,0,0); analogWrite(redPWM,map(currentValue2,0,maxValue,0,254)); }
      if (envelope2Phase==2) { setLeds(0,1,0,0); analogWrite(redPWM,map(currentValue2,0,maxValue,0,254)); }
      if (envelope2Phase==3) { setLeds(0,0,1,0); analogWrite(redPWM,map(currentValue2,0,maxValue,0,254)); }
      if (envelope2Phase==4) { setLeds(0,0,0,1); analogWrite(redPWM,map(currentValue2,0,maxValue,0,254)); }
    } else if (menuSelected) {
      //do nothing, do the led stuff inside the menu with setledcolor and setleds and ledstarttime
    } else { setLeds(0,0,0,0); } //expand this for the menu stuff etc...
  }
}


void setLedColor(byte color) {
  /*
  1 for on, 0 for off, color 0=channel1 and 1=channel2 (green or red)...
  1=GREEN,0=RED
  */
  if (color==0) { //RED
    analogWrite(greenPWM, 0);
    analogWrite(redPWM, 255);
  } else if (color==1) { //GREEN
    analogWrite(redPWM, 0);
    analogWrite(greenPWM, 255);
  } else if (color==2) { //YELLOW
    analogWrite(redPWM, 255);
    analogWrite(greenPWM, 255);
  } else  { //OFF
    analogWrite(redPWM, 0);
    analogWrite(greenPWM, 0);
  }
}  

void setLeds(bool led1on, bool led2on, bool led3on, bool led4on) {
  /*
  1 for on, 0 for off, color 0=channel1 and 1=channel2 (green or red)...
  */
  digitalWrite(led1,!led1on);
  digitalWrite(led2,!led2on);
  digitalWrite(led3,!led3on);
  digitalWrite(led4,!led4on);

} 

void menuLeds(byte led1Color, byte led2Color, byte led3Color, byte led4Color) {
  if (ledtimer<25) {
    //LED1 COLORS
    setLeds(1,0,0,0);
    if (led1Color==0) { digitalWrite(greenPWM,HIGH);digitalWrite(redPWM,LOW); } //green
    if (led1Color==1) { digitalWrite(greenPWM,LOW); digitalWrite(redPWM,HIGH); } //red
    if (led1Color==2) { digitalWrite(greenPWM,HIGH);digitalWrite(redPWM,HIGH); } //orange/yellow
    if (led1Color>=3) { digitalWrite(greenPWM,LOW); digitalWrite(redPWM,LOW); } //off.
  } else if (ledtimer<30) {
    digitalWrite(greenPWM,LOW); digitalWrite(redPWM,LOW); 
  } else if (ledtimer<55) {
    setLeds(0,1,0,0);
    if (led2Color==0) { digitalWrite(greenPWM,HIGH);digitalWrite(redPWM,LOW); }
    if (led2Color==1) { digitalWrite(greenPWM,LOW); digitalWrite(redPWM,HIGH); }
    if (led2Color==2) { digitalWrite(greenPWM,HIGH);digitalWrite(redPWM,HIGH); }
    if (led2Color>=3) { digitalWrite(greenPWM,LOW); digitalWrite(redPWM,LOW); }
  } else if (ledtimer<60) {
    digitalWrite(greenPWM,LOW); digitalWrite(redPWM,LOW);
  } else if (ledtimer<85) {
    setLeds(0,0,1,0);
    if (led3Color==0) { digitalWrite(greenPWM,HIGH);digitalWrite(redPWM,LOW); }
    if (led3Color==1) { digitalWrite(greenPWM,LOW); digitalWrite(redPWM,HIGH); }
    if (led3Color==2) { digitalWrite(greenPWM,HIGH);digitalWrite(redPWM,HIGH); }
    if (led3Color>=3) { digitalWrite(greenPWM,LOW); digitalWrite(redPWM,LOW); }
  } else if (ledtimer<90) {
    digitalWrite(greenPWM,LOW); digitalWrite(redPWM,LOW);
  } else if (ledtimer<115) {
    setLeds(0,0,0,1);
    if (led4Color==0) { digitalWrite(greenPWM,HIGH);digitalWrite(redPWM,LOW); }
    if (led4Color==1) { digitalWrite(greenPWM,LOW); digitalWrite(redPWM,HIGH); }
    if (led4Color==2) { digitalWrite(greenPWM,HIGH);digitalWrite(redPWM,HIGH); }
    if (led4Color>=3) { digitalWrite(greenPWM,LOW); digitalWrite(redPWM,LOW); }
  } else if (ledtimer<120) {
    digitalWrite(greenPWM,LOW); digitalWrite(redPWM,LOW);
  } else {
    setLeds(0,0,0,0); digitalWrite(greenPWM,LOW); digitalWrite(redPWM,LOW);
  }
  if (ledtimer==120) { ledtimer=0; } else { ledtimer++; }
}
