#include "core_esp8266_features.h"
#ifndef ws2812uu.h
#define ws2812uu.h
#include <Arduino.h>
void onelist(int iopinaa){
    int pp;
  for(pp=0;pp<8;pp++){
  digitalWrite(iopinaa, HIGH);
  delayMicroseconds(1);
  digitalWrite(iopinaa, LOW);
  delayMicroseconds(1);}
}



#endif