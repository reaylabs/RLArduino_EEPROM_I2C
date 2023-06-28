/*
RLArduino_EEPROM_I2C.cpp

Description
  I2C EEPROM library based on the Adafruit_EEPROM_I2C library.
  Added the ability to set the memory address byte count to handle
  a wider range of EEPROM memory sizes.

Author
  Robert Reay

Revision History
  11-21-2022 : Initial Code
*/
#include <math.h>
#include <stdlib.h>
#include "RLArduino_EEPROM_I2C.h"

//Constructor
RLArduino_EEPROM_I2C::RLArduino_EEPROM_I2C(void) {}

//Arduino begin function
bool RLArduino_EEPROM_I2C::begin(uint8_t addr, uint8_t address_size, TwoWire *theWire) {
  i2c_dev = new Adafruit_I2CDevice(addr,theWire);
  _addr = addr;
  _address_size = address_size;
  return i2c_dev->begin();
}

//Write a byte
bool RLArduino_EEPROM_I2C::write(uint32_t addr, uint8_t value) {
  uint8_t buff[5] = {0,0,0,0,0};  //Up to 4 address bytes plus data byte
  buildBuffer(addr, value, buff);
 
  // Write to EEPROM
  if (!i2c_dev->write(buff, (_address_size + 1)))
    return false;

  // Wait for acknowledge
  uint8_t timeout = 100;
  while (timeout--) {
    if (i2c_dev->detected())
      return true;
    delay(1);
  }

  //time out
  return false;
}

//Read a byte
uint8_t RLArduino_EEPROM_I2C::read(uint32_t addr) {
  uint8_t buff[5] = {0,0,0,0,0}; 
  buildBuffer(addr, 0 , buff);

  if (!i2c_dev->write_then_read(buff, _address_size, buff, 1))
    return 0x0;

  return buff[0];
}

//Write a buffer
bool RLArduino_EEPROM_I2C::write(uint32_t addr, uint8_t *buffer, uint16_t num) {
  while (num--) {
    if (!write(addr++, buffer[0])) {
      return false;
    }
    buffer++;
  }
  return true;
}

//Read multiple bytes and place in buffer
bool RLArduino_EEPROM_I2C::read(uint32_t addr, uint8_t *buffer, uint16_t num) {
  uint8_t buff[5] = {0,0,0,0,0}; 
  for (uint16_t i = 0; i < num; i++) {
    buildBuffer(addr, 0 , buff);
    if (!i2c_dev->write_then_read(buff, _address_size, buff, 1))
      return false;
    buffer[i] = buff[0];
    addr++;
  }

  return true;
}

//Build the address and data buffer
void  RLArduino_EEPROM_I2C::buildBuffer(uint32_t addr, uint8_t value, uint8_t *buffer)
{
  uint8_t address[4];
  memcpy(address, (void *)&addr, 4);
  for (int i = 0; i < _address_size; i++)
  {
    buffer[i] = address[i];
  }
  buffer[_address_size] = value;
}