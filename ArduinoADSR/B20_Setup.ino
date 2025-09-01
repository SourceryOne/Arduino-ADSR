void setup() {
  
  //Serial.begin(115200);
  //Serial.begin(57600);
  
  //PINSETUP
  pinMode(redPWM, OUTPUT);
  pinMode(greenPWM, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(9,OUTPUT); //OUTPUT2A
  pinMode(10,OUTPUT);  //OUTPUT2B
  pinMode(11,OUTPUT); //OUTPUT1A
  pinMode(3,OUTPUT); //OUTPUT1B
  
  pinMode(gatein1, INPUT_PULLUP);
  pinMode(gatein2, INPUT_PULLUP);

  pinMode(button1, INPUT);  // No pull-ups, active HIGH
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);

  TCCR1A = B10100001;  //Setting COM0A1,COM0A0, COM0B1, COM0B0 to 10 and 10 for Clear on compare set to bottom. And the WGM11 and WGM10 bits to 01 (along with WGM12 and WGM13 set to 00 in TCCR1B) for Phase correct PWM, 8 bit. (32kHz)
  //            v- set to 1 for 8 bit Fast PWM (64kHz)                     
  TCCR1B = B00000001; // Setting the WGM12 and WGM13 to 00 (see comments for TCCR1A above), and CS00, CS01, and CS02 bits for Prescaler /1 (001) 
  TCCR2A = B10100001;  //Setting COM0A1,COM0A0, COM0B1, COM0B0 to 10 and 10 for Clear on compare set to bottom. And the WGM11 and WGM10 bits to 01 (along with WGM12 and WGM13 set to 00 in TCCR1B) for Phase correct PWM, 8 bit. (32kHz)
  //            v- set to 1 for 8 bit Fast PWM (64kHz)                     
  TCCR2B = B00000001; // Setting the WGM12 and WGM13 to 00 (see comments for TCCR1A above), and CS00, CS01, and CS02 bits for Prescaler /1 (001) 
  //SETTING INITAL VALUES
  OCR1A = 0;
  OCR1B = 0;
  OCR2A = 0;
  OCR2B = 0;
  pinMode(13,OUTPUT); 
  
  setLeds(0,0,0,0);
  setLedColor(0);
    
  //int attack1RampDurationTime=1024;    //get from eeprom
  //attackValueCh1=1024;
  
  readEeprom(100);

  //The nDecay needs the original values of the maxvalues and sustainmultiplier.
  //originalMaxValue=maxValue;
  //originalSustainMultiplier=sustainMultiplier;
  
}
