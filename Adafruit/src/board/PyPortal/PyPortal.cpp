#include "PyPortal.h"

#define RED_LED       13
#define TFT_RESET     24
#define TFT_BACKLIGHT 25
#define LIGHT_SENSOR  A2
#define SD_CS         32       
#define SPKR_SHUTDOWN 50

#define TFT_D0        34 // Data bit 0 pin (MUST be on PORT byte boundary)
#define TFT_WR        26 // Write-strobe pin (CCL-inverted timer output)
#define TFT_DC        10 // Data/command pin
#define TFT_CS        11 // Chip-select pin
#define TFT_RST       24 // Reset pin
#define TFT_RD         9 // Read-strobe pin
#define TFT_BACKLIGHT 25

#define YP A4  // must be an analog pin, use "A
#define XM A7  // must be an analog pin, use "A
#define YM A6   // can be a digital pin
#define XP A5   // can be a digital pin
#define X_MIN  750
#define X_MAX  325
#define Y_MIN  840
#define Y_MAX  240

namespace PyPortal 
{
  Adafruit_ILI9341 tft = Adafruit_ILI9341(tft8bitbus, TFT_D0, TFT_WR, TFT_DC, TFT_CS, TFT_RST, TFT_RD);
  Adafruit_FlashTransport_QSPI flashTransport(PIN_QSPI_SCK, PIN_QSPI_CS, PIN_QSPI_IO0, PIN_QSPI_IO1, PIN_QSPI_IO2, PIN_QSPI_IO3);
  Adafruit_SPIFlash flash(&flashTransport);

  Adafruit_ADT7410 tempsensor = Adafruit_ADT7410(); 
  SdFat SD;
  TouchScreen touchInput = TouchScreen(XP, YP, XM, YM, 300);
  TSPoint touchPoint;

  void init()
  {
    pinMode(RED_LED, OUTPUT);
    enableBackLight();
    pinMode(TFT_RESET, OUTPUT);
    digitalWrite(TFT_RESET, HIGH);
    delay(10);
    digitalWrite(TFT_RESET, LOW);
    delay(10);
    digitalWrite(TFT_RESET, HIGH);
    delay(10);

    tft.begin();
    tft.fillScreen(ILI9341_BLACK);
    tft.setTextSize(2);
    tft.setTextColor(ILI9341_GREEN);
    tft.setTextWrap(true);
    tft.setCursor(0, 0);
    if (!flash.begin())
    {
      Serial.println("Could not find flash on QSPI bus!");
      tft.setTextColor(ILI9341_RED);
      tft.println("FAILED");
      while (1);
    }
    Serial.println("Reading QSPI ID");
    Serial.print("JEDEC ID: 0x"); Serial.println(flash.getJEDECID(), HEX);
    tft.setTextColor(ILI9341_GREEN);
    tft.print("QSPI Flash JEDEC 0x"); tft.println(flash.getJEDECID(), HEX);
  
    /*************** SD CARD */
    tft.setCursor(0, 48);
    tft.print("SD Card...");
    if (!SD.begin(SD_CS)) 
    {
      Serial.println("Card init. failed!");
      tft.setTextColor(ILI9341_RED);
      tft.println("FAILED");
      tft.setTextColor(ILI9341_GREEN);
    } 
    else 
    {
      tft.println("OK!");
    }

    /*************** WiFi Module */

    tft.setCursor(0, 64);
    tft.print("WiFi Module...");
    WiFi.status();
    delay(100);
    if (WiFi.status() == WL_NO_MODULE) 
    {
      Serial.println("ESP32 SPI not found");
      tft.setTextColor(ILI9341_RED);
      tft.println("FAILED");
      tft.setTextColor(ILI9341_GREEN);
    } 
    else 
    {
      Serial.println("ESP32 SPI mode found");
      tft.println("OK!");
    }

    /*************** Temperature sensor */
    tft.setCursor(0, 80);
    tft.print("ADT7410...");
    if (!tempsensor.begin()) 
    {
     tft.setTextColor(ILI9341_RED);
     tft.println("FAILED");
     tft.setTextColor(ILI9341_GREEN);
    } 
    else 
    { 
     tft.println("OK!");
    }

    //speaker
    analogWriteResolution(12);
    analogWrite(A0, 128);
    pinMode(SPKR_SHUTDOWN, OUTPUT);
    digitalWrite(SPKR_SHUTDOWN, LOW);
  }

  void enableBackLight(bool enable)
  {
    pinMode(TFT_BACKLIGHT, OUTPUT);
    if(true == enable)
      digitalWrite(TFT_BACKLIGHT, HIGH);
    else
      digitalWrite(TFT_BACKLIGHT, LOW);
  }

  void redLED(bool state)
  {
    if(false == state)
      digitalWrite(RED_LED, LOW);
    else
      digitalWrite(RED_LED, HIGH);
  }

  Adafruit_ILI9341& display()
  {
    return tft;
  }

  bool touch()
  {
    TSPoint p = touchInput.getPoint();
    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
    if (p.z > touchInput.pressureThreshhold) 
    {
      touchPoint.x = map(p.x, X_MIN, X_MAX, 0, display().width());
      touchPoint.y = map(p.y, Y_MIN, Y_MAX, 0, display().height());
      touchPoint.z = p.z;
      return true;
    }
    else
    {
      return false;
    }
  }

  TSPoint touchedCoord()
  {
    return touchPoint;
  }

  uint16_t lightSensor()
  {
    return analogRead(LIGHT_SENSOR);
  }

  float temperature()
  {
    return tempsensor.readTempC();
  }
}
