#include <EEPROM.h>
 
int eepromStartAddress=0;
bool done=false;

void setup() {
  //Serial.begin(9600);
  Serial.begin(115200);
  //Serial.begin(57600);  
}

void loop() {
  if (!done) {
    done=1;
    writeEeprom(1);
  } else {
    Serial.println("Done.");
  }
}
 
 
 
