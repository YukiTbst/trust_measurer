#ifndef HX711_
#define HX711_
#include "Arduino.h"
class HX711
{
  private:
  uint32_t bias;
  int sck;
  int dt;
  uint32_t onepulse();
  public:
  HX711(int sck_, int dt_);
  void set_up(int sck_, int dt_);
  uint32_t read_once();
  
};
#endif
