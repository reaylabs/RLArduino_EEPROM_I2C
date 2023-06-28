# RLArduino_EEPROM_I2C
  The RLArduino_EEPROM_I2C class is an extention of the Adafruit_EEPROM_I2C 
library that adds the ability to set the number of bytes for the EEPROM
memory address. EEPROM sizes of 2k bits/ 128 bytes and less use
1 address byte, while the larger sizes use 2 bytes. The Adafruit library
hardwired the address size to 2 bytes, so it would not work with the
smaller memory sizes.

## Dependancies
```C++
#include <Adafruit_I2CDevice.h>
#include <Arduino.h>
```

## Class RLArduino_EEPROM_I2C
```C++
RLArduino_EEPROM_I2C(void);
bool begin(uint8_t addr = EEPROM_DEFAULT_ADDRESS, uint8_t address_size = 2, TwoWire *theWire = &Wire);
bool write(uint32_t addr, uint8_t value);
uint8_t read(uint32_t addr);
bool write(uint32_t addr, uint8_t *buffer, uint16_t num);
bool read(uint32_t addr, uint8_t *buffer, uint16_t num);
template <class T> uint16_t writeObject(uint32_t addr, const T &value) 
template <class T> uint16_t readObject(uint32_t addr, T &value)
```

## Example
```C++
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