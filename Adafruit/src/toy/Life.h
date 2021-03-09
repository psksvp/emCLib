#pragma once

#include <stdint.h>
#include <Arduino.h>

template <size_t WIDTH, size_t HEIGHT>
class Life
{
  private:
    uint8_t current[WIDTH * HEIGHT];
    uint8_t next[WIDTH * HEIGHT];

  public:
    Life()
    {
      memset(current, 0, WIDTH * HEIGHT * sizeof(uint8_t));
      memset(next, 0, WIDTH * HEIGHT * sizeof(uint8_t));
    }

    size_t width() {return WIDTH;}
    size_t height() {return HEIGHT;}

    void init(int th)
    {
      randomSeed(analogRead(0));
      
      for(size_t i = 0; i < WIDTH * HEIGHT; i++)
      {
        current[i] = random(0, 100) > th ? 1 : 0;
        next[i] = 0;
      }
    }

    uint8_t countNeighbor(uint16_t x, uint16_t y)
    {
      return cell(x - 1, y - 1) + 
             cell(x, y - 1) + 
             cell(x + 1, y - 1) + 
             cell(x - 1, y) + 
             cell(x + 1, y) + 
             cell(x - 1, y + 1) + 
             cell(x, y + 1) + 
             cell(x + 1, y + 1);
    }

    uint8_t cell(uint16_t x, uint16_t y)
    {
       int ix = (x % WIDTH + WIDTH) % WIDTH;
       int iy = (y % HEIGHT + HEIGHT) % HEIGHT;
       int i = iy * WIDTH + ix;
       return current[i] > 0 ? 1 : 0;
    }

    void set(uint16_t x, uint16_t y, uint8_t value = 1, bool nextState = false)
    {
       int ix = (x % WIDTH + WIDTH) % WIDTH; 
       int iy = (y % HEIGHT + HEIGHT) % HEIGHT;
       int i = iy * WIDTH + ix;
       if(false == nextState)
        current[i] = value;
       else
        next[i] = value;
    }

    void evolve()
    {
      for(size_t y = 0; y < HEIGHT; y++)
      {
        for(size_t x = 0; x < WIDTH; x++)
        {
          uint8_t c = cell(x, y);
          int n = countNeighbor(x, y);
          if(1 == c)
          {
            set(x, y,  (2 == n || 3 == n ? 255 : 0), true);
          }
          else
          {
            set(x, y, (3 == n ? 255 : 0), true);
          }
        }
      }

      memcpy(current, next, WIDTH * HEIGHT * sizeof(uint8_t));
    }

    uint8_t* data() {return current;}
};
