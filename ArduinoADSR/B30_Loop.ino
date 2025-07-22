//250626 added sustainMultiplierCh1=sustainMultiplier; so it is reset when the nloop is done aswell.

void loop() {
  //Serial.println("");
  // Do all the menu stuff here.
  if (menuSelected) {
    updateMenu();
  }
  checkGates(); //Check the gates.
  catchPots(); //If the pots are released, then catch the pots and then read the values.

  if (envelope1Phase==40) { envelope1Phase=0; } //set the envelopephase to 0 for envelope 1.
  if (envelope2Phase==40) { envelope2Phase=0; } //set the envelopephase to 0 for envelope 2.
  
  //ACT FUNCTIONALITY
  switch(actCh1) {
    case 0:
      //GATE
      envelopeStartGate1();
       //Write envelope 1 if it is active
      break;
    case 1: 
      //TRIG
      envelopeStartTrig1();
      break;
    case 2:
      //LOOP
      envelopeStartLoop1();
      break;
    case 3:
      //nLOOP
      envelopeStartnLoop1();
      break;
  }
  envelopeWrite1();
  
  switch(actCh2) {
    case 0:
      //GATE
      envelopeStartGate2(); //Write envelope 2 if it is active
      break;
    case 1: 
      //TRIG
      envelopeStartTrig2();
      break;
    case 2:
      //LOOP
      envelopeStartLoop2();
      break;
    case 3:
      //nLOOP
      envelopeStartnLoop2();
      break;      
  }
  envelopeWrite2();


  
  controlLeds(); //if we are in envelopemode then control the LEDs...

  //Check the buttons....
  checkButton(1, button1, lastButton1, pressTime1);
  checkButton(2, button2, lastButton2, pressTime2);
  checkButton(3, button3, lastButton3, pressTime3);
  checkButton(4, button4, lastButton4, pressTime4);

  if (nLoop1Active==0) {
    maxValueCh1=maxValue;
    sustainMultiplierCh1=sustainMultiplier;
  }
  if (nLoop2Active==0) {
    maxValueCh2=maxValue;
    sustainMultiplierCh2=sustainMultiplier;
  }
  //Serial.print(sustainValueCh1); //the adding of the CV value to THIS variable messes upp the changing of channels and the values of the channel value, also when selecting target for cv messes up along the way...
  Serial.print (" attval: ");
  Serial.print(attackValueCh2);
  Serial.print (" gate: ");
  Serial.print(gate2Active);
  Serial.print (" phase: ");
  Serial.print(envelope2Phase);
  Serial.print (" rampdur:");
  Serial.print(rampDuration2);
  Serial.print (" val: ");
  Serial.println(currentValue2);
//   sustainValueCh1wCV=map(,0,1023,,1023); //or just limit the lower voltage?
  //Serial.println(sustainValueCh1wCV); //the adding of the CV value to THIS variable messes upp the changing of channels and the values of the 
/*  Serial.print (envelope1Phase);
  Serial.print (" ");
  Serial.print (nLoop1Active);
  Serial.print (nLoop1Count);
  Serial.println (nLoopLengthCh1);

*/
  


  
}
