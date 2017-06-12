/**
 * Created by Park, Nil on 2017-06-29.
 * Last Revision: 2017-04-27
 *
 * VitconNTCLink.h의 Description 참조
 */

#include "VitconNTCLink.h"
#include <Math.h>
#include <stdint.h>

using namespace vitcon;

NTCLink::NTCLink()
{
  // 25 Celsius - 10 Kohm, B = 4200 for NTC-10KD-5J
  // There may error rate depending on the thermistor specification.
  // Please change the values
  Init(25.0, 10000.0, 10000.0, 4200.0);
}

NTCLink::NTCLink(float t0, float r0, float b)
{
  Init(t0, r0, 1000.0, b);
}

NTCLink::NTCLink(float t0, float r0, float r1, float b)
{
  Init(t0, r0, r1, b);
}

void NTCLink::Init(float t0, float r0, float r1, float b)
{
  mT0 = t0;
  mR0 = r0;
  mR1 = r1;
  mB = b;
  mIsFirst = true;
  mIndex = 0;
}

float NTCLink::GetTemperature(int adc)
{
  // Moving average
  if (mIsFirst)
  {
    for (int i = 0; i < AVG_COUNT; i++)
      mSamples[i] = adc;
    mIsFirst = false;
  }
  else
    mSamples[mIndex++] = adc;
  if (mIndex >= AVG_COUNT)
    mIndex = 0;
  int32_t avg = 0;
  for (int i = 0; i < AVG_COUNT; i++)
    avg += mSamples[i];
    
  // Get NTC Resistance :   R1 / ( Amax / A - 1 )
  // came from   R / (R + R1) = A / Amax
  float avg_f = (float)avg / (float)AVG_COUNT;
  if (avg_f < 10.0)
    return INFINITY;
  if (avg_f > MAXADC - 10.0)
    return ABS_ZERO;
  float r = mR1 / (MAXADC / avg_f - 1.0);
  
  // Get Temperature :   1 / (1 / T0 + 1 / B * (ln (R / R0))
  // came from   steinhart equation 1 / T = 1 / T0 + 1 / B * ln (R / R0) in absolute temperature for T and T0
  return (1.0 / (1.0 / (mT0 - ABS_ZERO) + 1.0 / mB * log (r / mR0))) + ABS_ZERO;
}
