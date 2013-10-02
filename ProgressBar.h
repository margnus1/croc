#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

class ProgressBar 
{
 public:
  ProgressBar(int ticks, int width);
  void Tick();

 private:
  int ticks, width, tick;
};

#endif
