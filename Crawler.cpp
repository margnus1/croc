#include "CrocGame.h"

class Crawler
{
 public:
  Crawler (CrocSession *crocSession) : server (crocSession) {}
  void solve()
  {
    server->StartGame();
  }
  private:
    CrocSession *server;
};
