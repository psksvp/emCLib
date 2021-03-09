//  Created by psksvp on 12/1/20.
//  Copyright © 2020 psksvp. All rights reserved.
//

#ifndef __UTILS_FUNCTIONS__
#define __UTILS_FUNCTIONS__

#include <Arduino.h>

bool runSerialRead(void(*read)(const String&));
void blink(int);
int parseIntCSV(const String& s, int data[], unsigned int datalength);
int parseFloatCSV(const String& s, float data[], unsigned int datalength);

void reportSystemTypeSize();

template<class T>
void reportSize(const char* typeName)
{
  Serial.print("size of ");
  Serial.print(typeName);
  Serial.print(": ");
  Serial.println(sizeof(T));
}

template<class T>
T clamp(T v, T min, T max)
{
  if(v < min) 
    return min;
  if(v > max) 
    return max;
  
  return v;
}

template <class T> 
void swap(T& a, T& b)
{
  T t = a;
  a = b;
  b = t;
}

#endif