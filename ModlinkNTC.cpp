/*
 * ModlinkNTC.cpp
 *
 *  Created on: 2016. 6. 29.
 *      Author: Park, Kwang Seok
 */

#include "ModlinkNTC.h"
#include <Math.h>

ModlinkNTC::ModlinkNTC()
{
  // Based on NTC-10KD-5J
  Init(25.0, 10000.0, 4200.0);
}

ModlinkNTC::ModlinkNTC(float t0, float r0, float b)
{
  Init(t0, r0, b);
}

void ModlinkNTC::Init(float t0, float r0, float b)
{
  this->t0 = t0;
  this->r0 = r0;
  this->b = b;
  t = t0;

  // nominal adc at r0 :   Amax * R0 / (R1 + R0)
  // came from   R / (R + R1) = A / Amax
  float adc = MODLINK_NTC_MAXADC * r0 / (MODLINK_NTC_RESISTOR + r0);
  for (int i = 0; i < MODLINK_NTC_SAMPLES; i++)
  {
    samples[i] = (int)adc;
  }
  index = 0;

  // String formatter
//  str[0] = ' ';
//  str[1] = ' ';
//  str[2] = '2';
//  str[3] = '5';
//  str[4] = '.';
//  str[5] = '0';
//  str[6] = '0';
//  str[7] = '\0';
}

void ModlinkNTC::CalculateTemperature()
{
  // Moving average
  float avg = 0;
  for (int i = 0; i < MODLINK_NTC_SAMPLES; i++)
  {
    avg += (float)samples[i];
  }
  avg /= MODLINK_NTC_SAMPLES;
  // Get NTC Resistance :   R1 / ( Amax / A - 1 )
  // came from   R / (R + R1) = A / Amax
  float r = MODLINK_NTC_RESISTOR / (MODLINK_NTC_MAXADC / avg - 1);

  // Get Temperature :   1 / (1 / T0 + 1 / B * (ln (R / R0))
  // came from   steinhart equation 1 / T = 1 / T0 + 1 / B * ln (R / R0) in absolute temperature for T and T0
  //return (t0 + b / log (r / r0));
  t = (1.0 / (1.0 / (MODLINK_NTC_ABSOULTE_ZERO + t0) + 1.0 / b * log (r / r0))) - MODLINK_NTC_ABSOULTE_ZERO;
}

void ModlinkNTC::SetADC(int adc)
{
  samples[index] = adc;
  index = (index + 1) % MODLINK_NTC_SAMPLES;
  CalculateTemperature();
}

float ModlinkNTC::GetTemperature()
{
  return t;
}

float ModlinkNTC::GetTemperature(int adc)
{
  SetADC(adc);
  return t;
}
/*
int ModlinkNTC::GetTemperatureInt()
{
  float temp = t >= 0 ? t : -t;
  return (int)floor(temp);
}

int ModlinkNTC::GetTemperatureFixed(int precision)
{
  float temp = t >= 0 ? t : -t;
  float pre = pow(10, precision);
  return (int)(temp * pre) % (int)pre;
}

bool ModlinkNTC::IsPositive()
{
  return t >= 0;
}

const char* ModlinkNTC::GetString()
{
  int n = GetTemperatureInt();
  int f = GetTemperatureFixed(2);
  str[0] = t >= 0 ? ' ' : '-';
  str[3] = n % 10 + '0'; n /= 10;
  str[2] = (n == 0) ? ' ' : n % 10 + '0'; n /= 10;
  str[1] = (n == 0) ? ' ' : n % 10 + '0';
  str[5] = f / 10 + '0';
  str[6] = f % 10 + '0';
  str[7] = '\0';
  return str;
}*/
