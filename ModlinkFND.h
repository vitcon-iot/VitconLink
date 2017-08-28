/*
 * ModlinkFND.h
 *
 *  Created on: 2016. 8. 11.
 *      Author: Park, Kwang Seok
 */

#ifndef MODLINKFND_H_
#define MODLINKFND_H_

#include <Arduino.h>

#define MODLINKFND_DIGITS 4

void ModlinkFND_Init();

class ModlinkFND
{
private:
  uint8_t addr;
  uint8_t digits[MODLINKFND_DIGITS];
public:
  ModlinkFND(uint8_t addr);
  void SetNumber(uint16_t value);
  void SetNumber(uint8_t index, uint8_t value);
  void SetDot(uint8_t index);
  void SetMinus(uint8_t index);
  void SetByte(uint8_t index, uint8_t value);
  void Clear();
  void Clear(uint8_t index);
  void Send();
};

#endif /* MODLINKFND_H_ */
