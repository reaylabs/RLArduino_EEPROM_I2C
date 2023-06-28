/*
MultipleEEPROMTest.ino

Description
  Test of multiple EEPROM's with different memory sizes

Author
  Robert Reay

Revision History
  11-22-2022 : Initial Code
*/

#include "RLArduino_EEPROM_I2C.h"
RLArduino_EEPROM_I2C eeprom_1; //24LC025T 2k bit / 128 byte EEPROM
RLArduino_EEPROM_I2C eeprom_2; //24LC32ST 32k bit / 4k byte EEPROM

#define EEPROM_ADDRESS_1 0x50 
#define ADDRESS_SIZE_1 0x01  
#define EEPROM_ADDRESS_2 0x52
#define ADDRESS_SIZE_2 0x02 

void setup(void) {
  Serial.begin(115200);
    while(!Serial);

  //Initialize the EEPROMs
  if (eeprom_1.begin(EEPROM_ADDRESS_1, ADDRESS_SIZE_1)) { 
      Serial.println("Found I2C EEPROM 1");
  } else {
    Serial.println("I2C EEPROM_1 Not Found\r\n");
    while (1) delay(10);
  }
  if (eeprom_2.begin(EEPROM_ADDRESS_2, ADDRESS_SIZE_2)) { 
    Serial.println("Found I2C EEPROM 2");
  } else {
    Serial.println("I2C EEPROM 2 Not Found\r\n");
    while (1) delay(10);
  }
  
  //Write then read string from both EEPROMS
  uint8_t address = 0x00;
  Serial.println("\n** Different Memory Size EEPROM Read/Write Test **");  
  String outputString = "Hello World";
  String inputString_1 = "";
  String inputString_2 = "";
  Serial.println((String)"EEPROM: 1 Address: " + address + " Write: " + outputString);
  Serial.println((String)"EEPROM: 2 Address: " + address + " Write: " + outputString);
  eeprom_1.writeObject(address, outputString);
  eeprom_2.writeObject(address, outputString);
  eeprom_1.readObject(address, inputString_1);
  Serial.println((String)"EEPROM: 1 Address: " + address + " Read: " + inputString_1);
  eeprom_2.readObject(address, inputString_2);
  Serial.println((String)"EEPROM: 2 Address: " + address + " Read: " + inputString_2);
}

void loop(void) {

}
