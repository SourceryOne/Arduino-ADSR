void menu4() {
  /*
   * This is where it gets a bit "experimental" 
   * This is where we control CV input, nLoop/nDecay and EndOf functionality.
   */
  if (!channelSelect) { //These will only function on Channel 1 NO n's of nLOOP and nDecay needs to work for both channels!
      //if (actCh1==3) then set the FUNC for nLOOP to select how many loops from 0 (gated) to 15 or 16 or more...
    //EndOf... here or where?
    menuA1CV=attackPotValue;
    menuD1nDecay=decayPotValue;
    menuS1EndOf=sustainPotValue;
    menuR1nLoop=releasePotValue;
    //menuA1_4=attackPotValue;
    //menuD1_4=decayPotValue; //Could be decay of nLoops? 
    //menuS1_4=sustainPotValue; //End of...

      if (isBitSet(potsCaught,1)) {
        //nDecay
        nLoopDecayCh1=map(menuD1nDecay,0,1023,0,7); //100 is no decay
        if (nLoopDecayCh1==100) { menuLeds(3,3,3,3); 
        } else if (nLoopDecayCh1>5) { menuLeds(3,0,3,3); 
        } else if (nLoopDecayCh1>3) { menuLeds(3,2,3,3); 
        } else { menuLeds(3,1,3,3); }
      }
  
      if (isBitSet(potsCaught,3)) {
        //nLoopLength selector
        
        //menuR1nLoop=releasePotValue; //nLoop
        nLoopLengthCh1=map(menuR1nLoop,0,1023,0,16);
        switch(nLoopLengthCh1) {
          case 0:
            menuLeds(3,3,3,3);
            break;
          case 1:
            menuLeds(3,3,3,0);
            break;
          case 2:
            menuLeds(3,3,0,3);
            break;
          case 3:
            menuLeds(3,3,0,0);
            break;
          case 4:
            menuLeds(3,0,3,3);
            break;
          case 5:
            menuLeds(3,0,3,0);
            break;
          case 6:
            menuLeds(3,0,0,3);
            break;
          case 7:
            menuLeds(3,0,0,0);
            break;
          case 8:
            menuLeds(0,3,3,3);
            break;
          case 9:
            menuLeds(0,3,3,0);
            break;
          case 10:
            menuLeds(0,3,0,3);
            break;
          case 11:
            menuLeds(0,3,0,0);
            break;
          case 12:
            menuLeds(0,0,3,3);
            break;
          case 13:
            menuLeds(0,0,3,0);
            break;
          case 14:
            menuLeds(0,0,0,3);
            break;
          case 15:
            menuLeds(0,0,0,0);
            break;
          case 16:
            menuLeds(3,3,3,1);
            break;
        } 
      } 
      if (isBitSet(potsCaught,2)) {
        //EndOf selector
        
        //menuS1EndOf=sustainPotValue; //nLoop
        EndOfCh1=map(menuS1EndOf,0,1023,0,5);
        switch(EndOfCh1) {
          case 0: 
            //NO End of.
            menuLeds(3,3,3,3);
            break;
          case 1:
            //End of Attack.
            menuLeds(0,3,3,3);
            break;
          case 2:
            //End of Decay.
            menuLeds(3,0,3,3);
            break;
          case 3:
            //End of Sustain.
            menuLeds(3,3,0,3);
            break;
          case 4:
            //End of Release.
            menuLeds(3,3,3,0);
            break;
          case 5:
            //End of Release. Needs two because the mapped window is too small.
            EndOfCh1=4;
            menuLeds(3,3,3,0);
            break;
        }
      }
      
      if (isBitSet(potsCaught,0)) { //Attackpot.
        //CVControl selector.
      
        //menuA1CV=attackPotValue; //nLoop
        //OH! Add red leds for the CV to affect it negatively... :D green for positively ofcourse from the value set by the knob...
        //CVcontrol=map(menuA1CV,0,1023,0,5);
        CVcontrol=map(menuA1CV,0,1023,0,9);
        switch(CVcontrol) {
          case 0: 
            //NO CV.
            menuLeds(3,3,3,3);
            break;
          case 1:
            //CV on Attack.
            menuLeds(0,3,3,3);
            break;
          case 2:
            //CV on  Decay.
            menuLeds(3,0,3,3);
            break;
          case 3:
            //CV on Sustain.
            menuLeds(3,3,0,3);
            break;
          case 4:
            //CV on Release.
            menuLeds(3,3,3,0);
            break;
          case 5:
            //Negative CV on Attack.
            menuLeds(1,3,3,3);
            break;
          case 6:
            //Negative CV on  Decay.
            menuLeds(3,1,3,3);
            break;
          case 7:
            //Negative CV on Sustain.
            menuLeds(3,3,1,3);
            break;
          case 8:
            //Negative CV on Release.
            menuLeds(3,3,3,1);
            break;
          case 9:
            //CV on Release. Again one extra "window" because the map makes this one too small.
            CVcontrol=4;
            menuLeds(3,3,3,1);
            break;
        }
      }
  } else if (channelSelect) {
    //menuA2CV=attackPotValue;
    //menuS2EndOf=sustainPotValue;
    menuD2nDecay=decayPotValue;
    menuR2nLoop=releasePotValue;

    if (isBitSet(potsCaught,1)) {
      //nDecay
      nLoopDecayCh2=map(menuD2nDecay,0,1023,0,100); //100 is no decay
      if (nLoopDecayCh2==100) { menuLeds(3,3,3,3); 
      } else if (nLoopDecayCh2>75) { menuLeds(3,0,3,3); 
      } else if (nLoopDecayCh2>50) { menuLeds(3,2,3,3); 
      } else { menuLeds(3,1,3,3); }
    }
    
    if (isBitSet(potsCaught,3)) {
      nLoopLengthCh2=map(menuR2nLoop,0,1023,0,16);
      switch(nLoopLengthCh2) {
        case 0:
          menuLeds(3,3,3,3);
          break;
        case 1:
          menuLeds(3,3,3,0);
          break;
        case 2:
          menuLeds(3,3,0,3);
          break;
        case 3:
          menuLeds(3,3,0,0);
          break;
        case 4:
          menuLeds(3,0,3,3);
          break;
        case 5:
          menuLeds(3,0,3,0);
          break;
        case 6:
          menuLeds(3,0,0,3);
          break;
        case 7:
          menuLeds(3,0,0,0);
          break;
        case 8:
          menuLeds(0,3,3,3);
          break;
        case 9:
          menuLeds(0,3,3,0);
          break;
        case 10:
          menuLeds(0,3,0,3);
          break;
        case 11:
          menuLeds(0,3,0,0);
          break;
        case 12:
          menuLeds(0,0,3,3);
          break;
        case 13:
          menuLeds(0,0,3,0);
          break;
        case 14:
          menuLeds(0,0,0,3);
          break;
        case 15:
          menuLeds(0,0,0,0);
          break;
        case 16:
          menuLeds(3,3,3,2);
          break;
      } 
    } 
  }
  
}
