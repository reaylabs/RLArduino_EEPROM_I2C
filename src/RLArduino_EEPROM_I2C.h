/*
RLArduino_EEPROM_I2Ch

Description
  I2C EEPROM library based on the Adafruit_EEPROM_I2C library.
  Added the ability to set the memory address byte count to handle
  a wider range of EEPROM memory sizes.

Author
  Robert Reay

Revision History
  12-21-2022 : Initial Code
*/
#ifndef _REAYLABS_EEPROM_I2C_H_
#define _REAYLABS_EEPROM_I2C_H_

#include <Adafruit_I2CDevice.h>
#include <Arduino.h>

///<* 1010 + A2 + A1 + A0 = 0x50 default */
#define EEPROM_DEFAULT_ADDRESS (0x50)

//Class definition
class RLArduino_EEPROM_I2C {

public:
  RLArduino_EEPROM_I2C(void);
  bool begin(uint8_t addr = EEPROM_DEFAULT_ADDRESS, uint8_t address_size = 2, TwoWire *theWire = &Wire);
  bool write(uint32_t addr, uint8_t value);
  uint8_t read(uint32_t addr);
  bool write(uint32_t addr, uint8_t *buffer, uint16_t num);
  bool read(uint32_t addr, uint8_t *buffer, uint16_t num);

  //Write any object to memory
  template <class T> uint16_t writeObject(uint32_t addr, const T &value) {
    const byte *p = (const byte *)(const void *)&value;
    uint16_t n;
    for (n = 0; n < sizeof(value); n++) {
      write(addr++, *p++);
    }
    return n;
  }

  // Read any object from memory
  template <class T> uint16_t readObject(uint32_t addr, T &value) {
    byte *p = (byte *)(void *)&value;
    uint16_t n;
    for (n = 0; n < sizeof(value); n++) {
      *p++ = read(addr++);
    }
    return n;
  }

private:
  void buildBuffer(uint32_t addr, uint8_t value, uint8_t *buffer);

protected:
  Adafruit_I2CDevice *i2c_dev = NULL;  //The internal I2C device for communication
  uint8_t _addr = 0;
  uint8_t _address_size = 2;
};

#endif
