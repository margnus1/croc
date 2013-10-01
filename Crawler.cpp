#include "Crawler.h"
#include <vector>
#include <string>
#include <iostream>
#include "ToString.h"

void Crawler::play()
{
  int intdummies[10];
  double ddummies[10];
  int playerLocation;

  const int numberOfGames = 100;

  std::wstring action1;
  std::wstring action2;

  const std::vector<std::vector<int> >& paths = server->getPaths();

      server->StartGame();
      do {
	server->GetGameState(intdummies[0], playerLocation, 
			     intdummies[1], intdummies[2], ddummies[0], 
			     ddummies[1], ddummies[2]);
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
