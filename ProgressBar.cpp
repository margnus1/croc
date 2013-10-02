#include "ProgressBar.h"
#include <iostream>

ProgressBar::ProgressBar(int t, int w=80) : ticks(t), width(w), tick(0) {}
                                                                             
void ProgressBar::Tick()
{
  tick++;

  if (tick == ticks)
    std::cout << std::endl;

  else  if ( tick % (ticks / width)  == 0)
    std::cout << "+";
}
