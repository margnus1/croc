#ifndef CRAWLER_H
#define CRAWLER_H
#include "CrocGame.h"
#include <time.h>
#include <stdlib.h>

class Crawler
{
 public:
  Crawler (CrocSession *crocSession) : server (crocSession) {
    srand(time(NULL));
  }
  void play();

 private:
  CrocSession *server;
};

#endif
