#include "unihiker_k10.h"

UNIHIKER_K10 k10;
uint8_t screen_dir = 2;

// Renamed from 'near' to avoid compiler keyword conflicts
bool isNearlyEqual(double val, double expected)
{
  return std::abs(val - expected) < 0.0001;
}

void setup()
{
  k10.begin();
  k10.initScreen(screen_dir);
  k10.initBgCamerImage();
  k10.setBgCamerImage();
}
void loop()
{
}