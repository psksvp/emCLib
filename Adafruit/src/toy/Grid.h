#pragma once 

#include <stdint.h>
#include <Adafruit_GFX.h>
#include "Color.h"


template <T, size_t WIDTH, size_t HEIGHT>
class Grid
{
	T map[WIDTH * HEIGHT];
	
public:
	Grid()
	{
		memset(map, 0, WIDTH * HEIGHT * sizeof(T));
	}	
	
  size_t width() {return WIDTH;}
  size_t height() {return HEIGHT;}
	
	void set(int r, int c, T value, bool wrap = false)
	{
		if(true == wrap)
		{
			int ix = (x % WIDTH + WIDTH) % WIDTH;
			int iy = (y % HEIGHT + HEIGHT) % HEIGHT;
			int i = iy * WIDTH + ix;
			map[i] = value;
		}	
		else
			map[r * WIDTH + c] = value
	}	
	
	T value(int r, int c, bool wrap = false)
	{
		if(true == wrap)
		{
			int ix = (x % WIDTH + WIDTH) % WIDTH;
			int iy = (y % HEIGHT + HEIGHT) % HEIGHT;
			int i = iy * WIDTH + ix;
			return map[i];
		}	
		else
			return map[r * WIDTH + c];
	}
};


template <size_t WIDTH, size_t HEIGHT>
inline void gfxDrawGrid(Grid<uint16_t, WIDTH, HEIGHT>& g, GFXcanvas16& display)
{
  int w = (int)(display.width() / g.width());
  int h = (int)(display.height() / g.height());
  for(size_t y = 0; y < g.height(); y++)
  {
    for(size_t x = 0; x < g.width(); x++)
    {
      display.fillRect(x * w, y * h, w, h, g.value(y, x));
    }
  }
}		

