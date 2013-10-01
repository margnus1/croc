#include "Crawler.h"
#include <vector>
#include <string>
#include <iostream>

void Crawler::play()
{
  int intdummies[10];
  double ddummies[10];
  int playerLocation;
  int finalScore;

  const int numberOfGames = 100;

  std::wstring action1;
  std::wstring action2;

  const std::vector<std::vector<int> >& paths = server->getPaths();

  for(int i=0; i< numberOfGames; i++)
    {
      server->StartGame();
      do {
	server->GetGameState(intdummies[0], playerLocation, 
			     intdummies[1], intdummies[2], ddummies[0], ddummies[1], ddummies[2]);
	if(rand()%2)
	  action1='S';
	else
	  {
	    int size=paths[playerLocation].size();
	    action1=paths[playerLocation][rand()%size]-1;
	  }
	action2='S';
      } while(server->makeMove(action1, action2, finalScore));
      std::cout << "Game number: " << i+1 << "  \tScore: " << finalScore << std::endl;
    }
  server->PostResults();
  std::cout << "Number of games played: " << server->getPlayed() << std::endl;
  std::cout << "Avarage score: " << server->getAverage() << std::endl;
}
