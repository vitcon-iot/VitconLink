#include <VitconNTCLink.h>

using namespace vitcon;

NTCLink ntc1;
NTCLink ntc2;

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  float t0 = ntc1.GetTemperature(analogRead(A0));
  float t1 = ntc2.GetTemperature(analogRead(A1));
  Serial.print("Temperature: ");
  Serial.print(t0);
  Serial.print('\t');
  Serial.println(t1);

  delay(100);
}

