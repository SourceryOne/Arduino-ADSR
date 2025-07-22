
//============== PINASSIGNMENT ===================
const byte redPWM = 5;           // the PWM pin the LED is attached to. Change if wrong color is shown.
const byte greenPWM = 6;           // the PWM pin the LED is attached to. Change if wrong color is shown.
//pwm pins Ch1=11,3
//pwm pins Ch2=9,10
const byte led1=13;
const byte led2=12;
const byte led3=8;
const byte led4=7;


unsigned long ledStartTime=0;
unsigned int ledTimeout=0;
byte ledtimer;

const byte gatein1=2; // moved from pin 1 to be ale to do some serial monitoring and error checking... ;)
const byte gatein2=0; //MOVED AGAIN FROM A0 (14) TO ADD CV INPUT ASWELL! //A0 //moved from pin 0; //will be moved to a0 for cv input capabilities... CV input is done in parallell on A0.
const byte CVinput=14;
//unused pins: 2,4
//flytta en till analog pinne för att få en cv input... (eller två)

// Define potentiometer pins
const byte attackPot=18; //A4
const byte decayPot=19; //A5
const byte sustainPot=20; //A6
const byte releasePot=21; //A7

const byte button1=4; // moved from pin 14 (A0) to pin D4 to give gate2 cv input.
const byte button2=15; //A1
const byte button3=16; //A2
const byte button4=17; //A3


//============== Constants for functions in the code, can be altered to your liking... ===================
const bool debug=1;
//if (debug==1) { }
unsigned int maxValue = 61400; //61400 is just above 61380 which is 1023*60 (for sustain) 32768; //Removed const for nDecay to easily work. // 32,767 The maximum value we want to reach (was long), this might be a good value to "tune" as different circuits might have different maximums on this value?
unsigned int maxValueCh1 = maxValue; //for two independent maxValues while in nDecaymode for example.
unsigned int maxValueCh2 = maxValue;
//unsigned int originalMaxValue; //is set to maxValue in setup. Used for nDecay. Could be omited if using maxValueCh1 and Ch2 instead...

byte sustainMultiplier = 60;//63 because if it is 64 it becomes larger than decay and will make a mess of that part of the envelope. //32; //Removed const for nDecay to easily work. should correlate to the above value so at 1023*sustainMultiplier they are the same... 32 or 64. But 64 could be saved for Accent ;)
byte sustainMultiplierCh1 = sustainMultiplier;
byte sustainMultiplierCh2 = sustainMultiplier;
//byte originalSustainMultiplier; //is set to sustainMultiplier in setup. Used for nDecay. could be omitted if using two above Ch1, Ch2
const int menuHoldTime=500; //how long you should hold the button to go into hold menu. (in milliseconds).
//The three different time windows you can choose for each curve.
const int envelopeMultiplier0=0.5;
const int envelopeMultiplier1=5;
const int envelopeMultiplier2=50;

const bool advancedExponent=1; //Latest WORKS, but only between 0.5 and 3.5 with 1 in the middle. NOT WORKING!!!! if set to 0 the exponent is just three values as set below. In advanced mode you have a free running scale with left always being 1 and left and right be set below for more wild curves.
float exponentRange=3; // max-min so 3.5-0.5=3 used to center the exponent around 1.0=linear.
const float envelopeExponent0=0.5;
const float envelopeExponent1=1;
const float envelopeExponent2=3.5;


//Denna ska vara dynamiskt satt efter 60000 saves byt adress. antal och adress ska ligga i EEPROM.
int eepromStartAddress=0;



//byte is an alias for uint8_t, meaning it's an 8-bit unsigned integer that can store values from 0 to 255.

//int currentValue=0; one for each signal, this not needed.

bool channelSelect=0; //which channel i active and reads pots and shows on LEDs. 0 is ch1, 1 is ch2.
byte menuSelected=0; //a switch to show if a menu is selected or not. This affects the pots and leds.


long startTime=0;

//use rampDurationTime1,2,3 above instead, and set rampDurationCh1=rampduration1,2,3... o samma för Ch2.
int unsigned rampDuration1 = 1000; // The calculated value from attackValueCh1 * attack1Multiplier, also DSR... Ramp duration in milliseconds (1 second) actually 1023 (pot value)
int unsigned rampDuration2 = 1000; // Ramp duration in milliseconds (1 second) had to be int signed=30 sek, unsigned= 60 sek kanske tom long unsigned för really long.
long unsigned elapsedTime1=0;
long unsigned elapsedTime2=0;
byte attack1Multiplier=1; //1,10,100 som standard för ca 1,10 och 100 sekunders ramptid.
byte decay1Multiplier=1; //1,10,100 som standard för ca 1,10 och 100 sekunders ramptid.
byte release1Multiplier=1;
byte attack2Multiplier=1; //1,10,100 som standard för ca 1,10 och 100 sekunders ramptid.
byte decay2Multiplier=1; //1,10,100 som standard för ca 1,10 och 100 sekunders ramptid.
byte release2Multiplier=1;


//====================================================================================================================
//BUTTon STUFF XD
// Track button states
bool lastButton1 = LOW;
bool lastButton2 = LOW;
bool lastButton3 = LOW;
bool lastButton4 = LOW;

unsigned long pressTime1 = 0;
unsigned long pressTime2 = 0;
unsigned long pressTime3 = 0;
unsigned long pressTime4 = 0;

bool menuActive = false;  // Tracks if we are in menu mode
int activeButton = 0;     // Tracks which button entered menu mode

//============================ MENU STUFF============================================
//Menu stuff
int menuA1Multiplier, menuD1Multiplier, menuR1Multiplier, menuA2Multiplier, menuD2Multiplier, menuR2Multiplier; //multiplier in the menu which then is set to the final multiplier according to preset values.
int menuA1Exp, menuD1Exp, menuR1Exp, menuA2Exp, menuD2Exp, menuR2Exp; //exponential values of the ramp.
int menu1Mode, menu2Mode; //??? Whats this for? Ah, in mode settings... for MODE.
int menuR1nLoop, menuR2nLoop; //for the Func-menu.
int menuS1EndOf, menuS2EndOf; //Also for Func-menu
int menuA1CV; //third func-menu on the Attack for which input the CV should control. if any.
int menuD1nDecay, menuD2nDecay; //fourth function for the decay of the nLoops.

byte modeNr;
byte ledSegments=0b00000000;
byte menuLedColor1=0; //colors for the leds when inside the menu. 0-3 0=green, 1=red, 2=yellow, 3 and up=off
byte menuLedColor2=0;
byte menuLedColor3=0;
byte menuLedColor4=0;


   
//====================================================================================================================

bool gate1Active=0;
bool gate2Active=0;
//int trig1active=0;
//int trig1state=0;

byte envelope1Phase=0; //0=off. Start with 1=attack, 2=decay, 3=sustain and 4=release and go from there... when 2 is done, if mode=ad and If loop=1 then phase=1 for example... BUT an int takes up more space than four BOOL? Nope it does not... 1 Bool takes up 1BYTE, not one BIT!? use bitSet/bitRead to have 8 bool values in one byte.
byte envelope2Phase=0; //0=off, start with 1=attack, 2=decay, 3=sustain and 4=release and go from there...

//bool envelope1Initiation=0; // a variable to make sure that some things only happen once in the start of the envelope.      ***REMOVE USE BELOW INSTEAD
//bool envelope2Initiation=0; // a variable to make sure that some things only happen once in the start of the envelope.      
bool envelope1PhaseInitiation=0; // a variable to make sure that some things only happen once in the start of every phase in the envelope.      
bool envelope2PhaseInitiation=0; // a variable to make sure that some things only happen once in the start of every phase in the envelope.

int startingValueRelease1; //used where?
int startingValueRelease2;
//===================== Values for the curve values to keep if the knobs arent moved or used in another state/function =================
//envelope values 


unsigned int attackValueCh1;
unsigned int decayValueCh1;
unsigned int sustainValueCh1;
unsigned int releaseValueCh1;

unsigned int attackValueCh2;
unsigned int decayValueCh2;
unsigned int sustainValueCh2;
unsigned int releaseValueCh2;

//lin log antilog? 1=lin, 0.1= and 5.0=exponential 3.5 is most natural exponential growth. <1=fast start slow finish like caps. >1.0 slow start fast finish, exponential.
float attack1Exponent = 1.0;
float decay1Exponent = 1.0;
float release1Exponent = 1.0;
float attack2Exponent = 1.0;
float decay2Exponent = 1.0;
float release2Exponent = 1.0;

//byte attackEnvTypeCh2;
//byte decayEnvTypeCh2;
//byte releaseEnvTypeCh2;

byte nLoopLengthCh1, nLoopLengthCh2; //the amount of loops played when in nloopmode and trig is recieved.
byte nLoop1Active, nLoop2Active, nLoop1Count, nLoop2Count;
byte nLoopDecayCh1=100, nLoopDecayCh2=100;

byte CVcontrol; //which if any parameter the CV input should control.
int CVcontrolValue; //the value of the input signal.
int CVcontrolCount=0; //a counter so we dont check the CV too often.
int attackValueCh1wCV=0; //the value calculated from the pot + cv used in case CV is used and the pots should NOT change value when changing channel etc...
int decayValueCh1wCV=0;
int sustainValueCh1wCV=0;
int releaseValueCh1wCV=0;

//variables for catching the pots
byte potsCaught=0b00000000; //need to catche the pots first. First four bits are the four pots. OBS counting from the right!
byte wentAboveBelow=0b00000000; //set the first four bits if it goes above, and the four last bits if it goes below for the four pots...

unsigned int attackPotRead, decayPotRead, sustainPotRead, releasePotRead; //the value read from the pot so we dont read it too often.
int attackPotValue=0; //The final value to work with when the pots are caught and the value is read from the pot: attackPotValue = attackPotRead; 
int decayPotValue=0;
int sustainPotValue=0;
int releasePotValue=0;
byte catchPotsTimer=0;
//int attackPotReadOld, decayPotReadOld, sustainPotReadOld, releasePotReadOld;
//byte lastPotTurned;

// Define the target value and the ramp duration
int buttonCheckInterval = 100; //The loop interval between checking buttons, to make sure the envelope is not interupted too much...
unsigned int currentValue1=0; //current value of the first envelope.
unsigned int currentValue2=0; //current value of the 2nd envelope.
unsigned long startTime1=0; //The start time of the first envelope, reset for each phase in the ADSR.
unsigned long startTime2=0; //The start time of the first envelope, reset for each phase in the ADSR.

//int sustainLevel=0;

//byte modeCh1=0b00001111;  //00000000 11110000=ADSR 1111 //bitwise check READING FROM THE RIGHT!!! Loop on bit 5?
//byte modeCh2=0b00001111; //		(ADSR, AD, 2xAD) READING FROM THE RIGHT!!!!!
//Remove the two above and use these instead
//bool loopCh1, loopCh2; //if we are in loop or not.
byte actCh1, actCh2; //how each channel acts, GATE, TRIG, LOOP or nLOOP.
//byte nLoopCh1, nLoopCh2; //the amount of loops played when in nloopmode and trig is recieved.
byte EndOfCh1; //, EndOfCh2; //Which stage triggers the EndOf on channel1, but channel two?
//bool att1Active, dec1Active, sus1Active, rel1Active; //active is the wrong word. used?
//bool att2Active, dec2Active, sus2Active, rel2Active; //USES THE envelope1phase instead.
byte moduleMode;
/*
 * Modes:
 * Dual ADSR yellow
 * 1 ADSR 2 outputs 2&4 green
 * toggled adsr 1yellow 2green 4red
 * accented adsr 2outputs green green black red
 * accented adsr 1output greenyellowred
 * loop
 */
// loopEnabledCh1 
// loopCh2
// selectedChannel 1or 2 eller 0 o 1
