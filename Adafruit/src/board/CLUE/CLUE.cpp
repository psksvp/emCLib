#include "CLUE.h"
#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM6DS33.h>
#include <Adafruit_LIS3MDL.h>
#include <Adafruit_SHT31.h>
#include <Adafruit_APDS9960.h>
#include <Adafruit_BMP280.h>

#define WHITE_LED 43

namespace CLUE
{
  Adafruit_Arcada arcada;
  Adafruit_LSM6DS33 lsm6ds33;
  Adafruit_LIS3MDL lis3mdl;
  Adafruit_SHT31 sht30;
  Adafruit_APDS9960 apds9960;
  Adafruit_BMP280 bmp280;

  IMU imuData;

  GFXcanvas16 canvas16(240, 240);

  bool init()
  {
    if(arcada.arcadaBegin())
    {
      arcada.displayBegin();
      apds9960.begin();
      lsm6ds33.begin_I2C();
      lis3mdl.begin_I2C();
      sht30.begin(0x44);
      bmp280.begin();
      pinMode(WHITE_LED, OUTPUT);
      return true;
    }
    else 
    {
      return false;
    }
  } 
  
  void setBacklight(uint8_t l)
  {
    arcada.setBacklight(l);
  }

  float temperature()
  {
    return bmp280.readTemperature();
  }

  float airPressure()
  {
    return bmp280.readPressure() / 100.0f;
  }

  float altitude()
  {
    return bmp280.readAltitude();
  }

  float humidity()
  {
    return sht30.readHumidity();
  }

  float light()
  {
    uint16_t r, g, b, c;
    while(!apds9960.colorDataReady())
    {
      delay(5);
    }
    apds9960.getColorData(&r, &g, &b, &c);
    return c;
  }

  IMU& imu()
  {
    sensors_event_t temp;
    lsm6ds33.getEvent(&imuData.accelerometer,
                      &imuData.gyroscope,
                      &temp);
    lis3mdl.getEvent(&imuData.magnetometer);
    return imuData;
  }

  GFXcanvas16& canvas()
  {
    return canvas16;
  }

  void updateDisplay()
  {
    arcada.display->drawRGBBitmap(0, 0, canvas16.getBuffer(), 240, 240);
  }

  uint8_t readButtons()
  {
    return arcada.readButtons();
  }

  bool buttonA()
  {
    return readButtons() & ARCADA_BUTTONMASK_A ? true : false;
  }

  bool buttonB()
  {
    return readButtons() & ARCADA_BUTTONMASK_B ? true : false;
  }


  void print(const char* s)
  {
    arcada.display->print(s);
  }

  void whiteLED(bool on)
  {
    digitalWrite(WHITE_LED, true == on ? HIGH : LOW);
  }

  void playTone(unsigned int freq, unsigned long duration)
  {
    ::tone(ARCADA_AUDIO_OUT, freq, duration);
  }

  Adafruit_Arcada& arcada()
  {
    return arcada;
  }

  /*
  def compassHeading(declicationDeg=-90, declicationMin=6.0):
    declination = (declicationDeg + declicationMin / 60.0) * (math.pi / 180.0)
    x, y, _ = clue.magnetic
    headingRad = math.atan2(y, x)
    headingRad = headingRad + declination
    if headingRad < 0:
        headingRad = headingRad + (2 * math.pi)
    
    if headingRad >= 2 * math.pi:
        headingRad = headingRad - (2 * math.pi)

    headingDeg = headingRad * 180.0 / math.pi
    degrees = math.floor(headingDeg)
    minutes = math.ceil((headingDeg - degrees) * 60.0)
    return (degrees, minutes)
  */

}
