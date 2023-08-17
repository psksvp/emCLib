#pragma once

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_SPIFlash.h>
#include <Adafruit_ADT7410.h>
#include <TouchScreen.h>
#include <SdFat.h>
#include <WiFiNINA.h>

namespace PyPortal
{
  void init();
  void enableBackLight(bool enable = true);
  void redLED(bool state);
  Adafruit_ILI9341& display();
  bool touch();
  TSPoint touchedCoord();
  uint16_t lightSensor();
  float temperature();
}
