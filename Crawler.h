#ifndef CRAWLER_H
#define CRAWLER_H
#include "CrocGame.h"
#include <time.h>
#include <stdlib.h>
#include <dijkstra.h>

class Crawler
{
 public:
  int finalScore;

  Crawler (CrocSession *crocSession)
    : server (crocSession),
    dijkstra(server->getPaths()) {
    srand(time(NULL));
  }
  void play();

 protected:
  CrocSession *server;
  Dijkstra dijkstra;
};

#endif
