#include "Crawlernew.h"
#include <vector>
#include <string>
#include <iostream>
#include "ToString.h"

void _Crawler::play()
{
  const std::vector<std::vector<int> >& paths = server->getPaths();

      server->StartGame();
      do {
	  getData();
	  backPackers();
	  water();
	  calcNewProbs();
	  choseActions();
	  update();
      } while(server->makeMove(action1, action2, finalScore));
}

void _Crawler::getData()
{
  server->GetGameState(score, playerLocation, 
		      backpacker1Activity, backpacker2Activity, 
		      calcium, saline, alkalinity);
}

void _Crawler::choseActions()
{
  // Code
}