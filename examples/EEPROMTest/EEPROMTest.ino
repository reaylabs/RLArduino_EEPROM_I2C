
/*
EEPROMTest.ino

Description
  This is a test of the RLArduino_EEPROM_I2C library.

Author
  Robert Reay

Revision History
  11-22-2022 : Initial Code
*/

#include "RLArduino_EEPROM_I2C.h"
RLArduino_EEPROM_I2C i2ceeprom;

#define EEPROM_ADDRESS 0x50 //I2C address of the EEPROM
#define ADDRESS_SIZE 0x01   //Number of bytes in the EEPROM memory location address (1-4)

void setup(void) {
  Serial.begin(115200);
  while(!Serial);
  
  //Initialize the EEPROM
  if (i2ceeprom.begin(EEPROM_ADDRESS, ADDRESS_SIZE)) { 
    Serial.println("Found I2C EEPROM");
  } else {
    Serial.println("I2C EEPROM Not Found\r\n");
    while (1) delay(10);
  }
  
  //EEPROM memory locaction address
  uint8_t address = 0;

  //Byte Test
  Serial.println("\n** Byte Read/Write Test **");
  for (address = 0; address < 2; address++)
  {
    Serial.println((String)"Address " + address + " Write " + address);
    i2ceeprom.write(address, address);
  }
  for (address = 0; address < 2; address++)
  {
    Serial.println((String)"Address " + address + " Read " + i2ceeprom.read(address));  
  }

  //Buffer Test
  address = 0x03;
  Serial.println("\n** Buffer Read/Write Test **");
  uint8_t outBuffer[5] = {0xF1,0xF2,0xF3,0xF4,0xF5};
  uint8_t inBuffer[5] = {0, 0, 0, 0, 0};
  Serial.print((String)"Address " + address + " Write ");
  for (int i = 0; i < 5; i++)
  {
    Serial.print(outBuffer[i], HEX);
    Serial.print(" ");
  }
  Serial.println("");
  i2ceeprom.write(address, outBuffer, 5);
  Serial.print((String)"Address " + address + " Read ");
  i2ceeprom.read(address, inBuffer, 5);
  for (int i = 0; i < 5; i++)
  {
    Serial.print(inBuffer[i], HEX);
    Serial.print(" ");
  }
  Serial.println("");

  //Float Test 
  address = 0x08;
  Serial.println("\n** Float Read/Write Test **");  
  float pi = 3.14159;
  Serial.print((String)"Address " + address + " Write ");
  Serial.println(pi,5);
  i2ceeprom.writeObject(address, pi);
  float x;
  i2ceeprom.readObject(address, x);
  Serial.print((String)"Address " + address + " Read ");
  Serial.println(x,5);

  //String Test 
  address = 0x0C;
  Serial.println("\n** String Read/Write Test **");  
  String outputString = "Hello World";
  String inputString = "";
  Serial.println((String)"Address " + address + " Write " + outputString);
  i2ceeprom.writeObject(address, outputString);
  i2ceeprom.readObject(address, inputString);
  Serial.println((String)"Address " + address + " Read " + inputString);
}

void loop(void) {

}
