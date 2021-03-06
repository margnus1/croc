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
	if(rand()%2)
	  action1='S';
	else
	  {
	    int size=paths[playerLocation-1].size();
	    action1 = ToString((long long)paths[playerLocation-1][rand()%size]);
	  }
	action2='S';
      } while(server->makeMove(action1, action2, finalScore));
}
