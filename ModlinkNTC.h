/*
 * ModlinkNTC.h
 *
 *  Created on: 2016. 6. 29.
 *      Author: Park, Kwang Seok
 */

#ifndef MODLINKNTC_H_
#define MODLINKNTC_H_

#define MODLINK_NTC_SAMPLES 20 // moving average count
#define MODLINK_NTC_RESISTOR 1000.0 // 1 kohm
#define MODLINK_NTC_MAXADC 1023.0 // maximum ADC value (5V)
#define MODLINK_NTC_ABSOULTE_ZERO 273.15
//#define MODLINK_NTC_PRINT_LEN 8

class ModlinkNTC
{
private:
  int samples[MODLINK_NTC_SAMPLES];
  int index;
  float t0; // nominal temperature of NTC sensor
  float r0; // nominal resistance of NTC sensor
  float b; // coefficient of NTC sensor
  float t; // calculated when SetADC(int) or GetTemperature(int) have been called
  //char str[MODLINK_NTC_PRINT_LEN]; // printable format
  void Init(float t0, float r0, float b);
  void CalculateTemperature();
public:
  ModlinkNTC();
  ModlinkNTC(float t0, float r0, float b);
  void SetADC(int adc);
  float GetTemperature();
  float GetTemperature(int adc); // combined GetTemperature with SetADC
  //int GetTemperatureInt(); // integer part (absolute number)
  //int GetTemperatureFixed(int precision); // fixed point part (absolute number)
  //bool IsPositive();
  //const char * GetString(); // get printable format. +XXX.XX (seven characters)
};

#endif /* MODLINKNTC_H_ */
