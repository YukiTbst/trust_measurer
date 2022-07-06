#include "Arduino.h"
#include "HX711.h"
HX711::HX711(int sck_, int dt_)
{
  sck=sck_;
  dt=dt_;
  pinMode(dt,INPUT);
  pinMode(sck, OUTPUT);
  read_once();
}
void HX711::set_up(int sck_, int dt_)
{
  sck=sck_;
  dt=dt_;
  pinMode(dt,INPUT);
  pinMode(sck, OUTPUT);
  read_once();
}
uint32_t HX711::onepulse()
{
  uint32_t res=0;
  digitalWrite(sck,HIGH);
  delayMicroseconds(1);
  if(digitalRead(dt)==HIGH)
  {
    res=1;
  }
  digitalWrite(sck, LOW);
  delayMicroseconds(1);
  return res; 
}
uint32_t HX711::read_once()
{
  uint32_t result=0;
  while(digitalRead(dt)==HIGH)
  {
  }
  delayMicroseconds(1);
  for(int i=0; i<24; i++)
  {
    result*=2;
    result+=onepulse();
  }
  for(int i=0;i<1; i++)
  {
    onepulse();
  }
  return result;  
}