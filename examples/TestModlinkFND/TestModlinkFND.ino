#include "ModlinkFND.h"

ModlinkFND fnd(0);

void setup() {
  ModlinkFND_Init();
  delay(1000);
  fnd.SetNumber(1234);
  fnd.Send();
  delay(1000);
  fnd.SetNumber(5678);
  fnd.Send();
  delay(1000);
  fnd.SetNumber(9012);
  fnd.Send();
  delay(1000);
  fnd.SetDot(3);
  fnd.Send();
  delay(1000);
  fnd.SetDot(2);
  fnd.Send();
  delay(1000);
  fnd.SetDot(1);
  fnd.Send();
  delay(1000);
  fnd.SetDot(0);
  fnd.Send();
  delay(1000);
  fnd.SetNumber(0, 3);
  fnd.Send();
  delay(1000);
  fnd.SetNumber(1, 4);
  fnd.Send();
  delay(1000);
  fnd.SetMinus(2);
  fnd.Send();
  delay(1000);
  fnd.Clear(3);
  fnd.Send();
  delay(1000);
  fnd.SetByte(1, 0b01110000);
  fnd.Send();
  delay(1000);
  fnd.Clear();
  fnd.Send();
}

void loop(void){                                  
}
