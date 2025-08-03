void menu3() {
  //Set MODE
  //DOESNT MATTER WHICH CHANNEL, THIS AFFECTS BOTH CHANNELS
  /* 
  0 = Dual ADSR Dual Output - all yellow
  1 = 1 ADSR 2 Outputs (ADSR1 on both outputs) - green green 0 green 
  2 = 2 ADSR 1 output (ADSR1 och ADSR2 on same output... hmm how?) - green yellow red 0
  3 = Toggled ADSR (ADSR1 and ADSR2 on output 1 & 2 toggled between the two from input 1?) - 
  4 = Accented ADSR 1 output 
  5 = Accented ADSR 2 outputs (why?)
  6 = Dual AD - green green red red. NAH, wont work nice with the colors...?

  EO... EndOf ADSR either output trig at that point or start the other ADSR.
  7. New idea for mode, to use the module as an offset module, just sending +5v on each output. and then using the intenuverters to control how much output. show as green out red out. (0g0r)

  
  */
  menu1Mode=attackPotValue;
  //moduleMode=map(menu1Mode, 0, 1023, 0, 6); THIS WOULD WORK AGAIN NOW, BUT ALREADY DID BELOW, WHICH IS PROBABLY MORE EFFIECENT...

       if (menu1Mode<=170) {moduleMode=0; menuLeds(0,0,1,1); }      //Dual ADSR, yyyy. should be ggrr no?
  else if (menu1Mode<=341) {moduleMode=1; menuLeds(0,0,3,0); } //1 input 1 ADSR 2 Outputs (normally coupled type thing), gg0g GAH !!!!! WHAT DO I EVEN MEAN 1input, that plays both adsrs on both outputs or the SAME ADSR on BOTH outputs?
  else if (menu1Mode<=512) {moduleMode=2; menuLeds(0,0,3,1); } //1 input 2 ADSR 2 outputs
  //else if (menu1Mode<=512) {moduleMode=2; menuLeds(0,0,3,1); } //2 input 2 ADSR 1 output (ADSR1 och ADSR2 on same output... this is like the Accented one but they would interfere...? - green yellow red 0
  else if (menu1Mode<=682) {moduleMode=3; menuLeds(0,1,0,1); } //Toggled ADSR (ADSR1 and ADSR2 on output 1 & 2 toggled between the two from input 1?) - 
  else if (menu1Mode<=852) {moduleMode=4; menuLeds(0,0,3,0); } //Accented ADSR 1 output, and/or Accented ADSR 2 outputs (why?) just flip them?
  else if (menu1Mode<=1023){moduleMode=5; menuLeds(0,0,3,0); } //Dual AD - green green red red. NAH, wont work nice with the colors...?
  
  
  //if (moduleMode==0) { menuLeds(2,2,2,2); } //Dual ADSR, yyyy. 
  //if (moduleMode==1) { menuLeds(0,0,3,0); } //1 ADSR 2 Outputs, gg0g

  //menuLeds(menuLedColor1,menuLedColor2,3,menuLedColor4);
  
}
