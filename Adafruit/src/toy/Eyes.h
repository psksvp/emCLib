#pragma once 

#include <Adafruit_GFX.h>
#include "Color.h"

class Eyes
{
  int16_t eyeDistance;
  int16_t eyeWidth, eyeHeight;
  int16_t screenWidth, screenHeight;
  int16_t pupilRadius = 10;

  int16_t lookAtX, lookAtY;

  public:

  Eyes(int16_t width, int16_t height)
  {
    screenWidth = width;
    screenHeight = height;
    eyeDistance = (int16_t)(width * 0.2);
    eyeWidth = (int16_t)(width * 0.3);
    eyeHeight = (int16_t)(height * 0.4);
    lookAtX = width / 2;
    lookAtY = height / 2;
  }

  void lookAt(int16_t mx, int16_t my)
  {
    lookAtX = mx;
    lookAtY = my;
  }

  void draw(Adafruit_GFX& gfx)
  {
    gfx.fillRect(0, 0, screenWidth, screenHeight, RGB16(200, 200, 200));
    int eyeX = (screenWidth - eyeWidth)  / 2 - eyeDistance;
    int eyeY = (screenHeight - eyeHeight) / 2;
    drawEye(gfx, eyeX, eyeY);
    drawEye(gfx, eyeX + 2 * eyeDistance, eyeY);
  }

  void drawEye(Adafruit_GFX& gfx, int16_t x, int16_t y)
  {
    gfx.fillRoundRect(x, y, eyeWidth, eyeHeight, 20, RGB16(0,255,0));

    float mx = lookAtX;
    float my = lookAtY;
    float x2 = mx/((float)eyeWidth/eyeHeight);
    float t = max(1, sqrt(x2*x2 + my * my)/(eyeHeight/2));
    float sx = mx / t, sy = my/t;

    int16_t px = (int)(x + sx + pupilRadius);
    int16_t py = (int)(y + sy + pupilRadius);

    gfx.fillCircle(px, py, pupilRadius, 0);
  }

};