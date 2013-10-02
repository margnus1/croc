#include "Crawler.h"
#include <vector>
#include <string>
#include <iostream>
#include "ToString.h"

void Crawler::play()
{
  int score;
  int playerLocation;
  int backpacker1Activity;
  int backpacker2Activity;
  double calcium;
  double saline;
  double alkalinity;

  std::wstring action1;
  std::wstring action2;

  const std::vector<std::vector<int> >& paths = server->getPaths();

      server->StartGame();
      do {
	server->GetGameState(score, playerLocation, 
			     backpacker1Activity, backpacker2Activity, 
			     calcium, saline, alkalinity);

	// Code

      } while(server->makeMove(action1, action2, finalScore));
}
