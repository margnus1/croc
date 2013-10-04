#ifndef _CRAWLER_H
#define _CRAWLER_H
#include "CrocGame.h"
#include <time.h>
#include <stdlib.h>

class _Crawler
{
 public:
  int getFinalScore();
  
  _Crawler (CrocSession *crocSession) : server (crocSession) {
    srand(time(NULL));
  }
  void play();

 private:
  void init();
  void getData();
  void backPackers();
  void water();
  void calcNewProbs();
  void choseActions();
  void update();
  
  int finalScore;

  int score;
  int playerLocation;
  int backpacker1Activity;
  int backpacker2Activity;
  double calcium;
  double saline;
  double alkalinity;
  wstring action1;
  wstring action2;
  const vector<vector<int> >& paths = server->getPaths();
  const int noNodes = paths.size();

  CrocSession *server;
};

#endif
