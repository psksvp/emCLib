#pragma once 

#define RGB16(r, g, b) (((31*(r+4))/255)<<11) | (((63*(g+2))/255)<<5) | ((31*(b+4))/255)