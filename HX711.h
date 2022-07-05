#ifndef HX711
#define HX711
#include "Arduino.h"
class HX711
{
  private:
  uint32_t bias;
  int sck;
  int dt;
  uint32_t onepulse();
  public:
  void set_up(int sck_, int dt_);
  uint32_t read_once();
  HX711(int sck_, int dt_);
};
#endif
