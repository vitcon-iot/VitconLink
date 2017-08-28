/*
 * ModlinkFND.cpp
 *
 *  Created on: 2016. 8. 11.
 *      Author: Park, Kwang Seok
 */

#include "ModlinkFND.h"
#include <Wire.h>

static const uint8_t SAA1064T_ADDR_COUNT = 4;
static const uint8_t SAA1064T_ADDR[SAA1064T_ADDR_COUNT] = { 0x38, 0x39, 0x40, 0x41 };
static const uint8_t SAA1064T_CONFIG0 = 0b00000000;
static const uint8_t SAA1064T_CONFIG1 = 0b01000111;

static const uint8_t FND_DIGITS[10]
  = { 0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110,
      0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111 }; // from 0 to 9
static const uint8_t FND_DIGIT = 0b01111111;
static const uint8_t FND_DOT = 0b10000000;
static const uint8_t FND_MINUS = 0b01000000;
static const uint8_t FND_CLEAR = 0b00000000;

void ModlinkFND_Init()
{
  Wire.begin();
  for (uint8_t i = 0; i < SAA1064T_ADDR_COUNT; i++)
  {
    Wire.beginTransmission(SAA1064T_ADDR[i]);
    Wire.write(SAA1064T_CONFIG0);
    Wire.write(SAA1064T_CONFIG1);
    Wire.endTransmission();
  }
}

ModlinkFND::ModlinkFND(uint8_t addr)
{
  this->addr = SAA1064T_ADDR[min(addr, SAA1064T_ADDR_COUNT - 1)];
  Clear();
}

void ModlinkFND::Send()
{
  Wire.beginTransmission(addr);
  Wire.write(1);
  for (uint8_t i = 0; i < MODLINKFND_DIGITS; i++)
  {
    Wire.write(digits[i]);
  }
  Wire.endTransmission();
}

void ModlinkFND::SetNumber(uint16_t value)
{
  if (value > pow(10, MODLINKFND_DIGITS) - 1)
  {
    for (uint8_t i = 0; i < MODLINKFND_DIGITS; i++)
    {
      digits[i] = (FND_DIGITS[9] & FND_DIGIT) | (digits[i] & ~FND_DIGIT);
    }
  }
  else
  {
    uint16_t r = value;
    uint16_t m = pow(10, MODLINKFND_DIGITS - 1);
    for (uint8_t i = 0; i < MODLINKFND_DIGITS; i++)
    {
      digits[i] = (FND_DIGITS[r/m] & FND_DIGIT) | (digits[i] & ~FND_DIGIT);
      r %= m;
      m /= 10;
    }
  }
}
void ModlinkFND::SetNumber(uint8_t index, uint8_t value)
{
  if (index < MODLINKFND_DIGITS)
  {
    if (value > 9)
    {
      digits[index] = (FND_DIGITS[9] & FND_DIGIT) | (digits[index] & ~FND_DIGIT);
    }
    else
    {
      digits[index] = (FND_DIGITS[value] & FND_DIGIT) | (digits[index] & ~FND_DIGIT);
    }
  }
}

void ModlinkFND::SetDot(uint8_t index)
{
  for (uint8_t i = 0; i < MODLINKFND_DIGITS; i++)
  {
    if (index == i)
    {
      digits[i] |= FND_DOT;
    }
    else
    {
      digits[i] &= ~FND_DOT;
    }
  }
}

void ModlinkFND::SetMinus(uint8_t index)
{
  if (index < MODLINKFND_DIGITS)
  {
    digits[index] = (FND_MINUS & FND_DIGIT) | (digits[index] & ~FND_DIGIT);
  }
}

void ModlinkFND::SetByte(uint8_t index, uint8_t value)
{
  if (index < MODLINKFND_DIGITS)
  {
    digits[index] = value;
  }
}

void ModlinkFND::Clear()
{
  for (uint8_t i = 0; i < MODLINKFND_DIGITS; i++)
  {
    digits[i] = FND_CLEAR;
  }
}

void ModlinkFND::Clear(uint8_t index)
{
  if (index < MODLINKFND_DIGITS)
  {
    digits[index] = FND_CLEAR;
  }
}