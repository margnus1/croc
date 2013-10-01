#include "Crawler.h"
#include <vector>
#include <string>
#include <iostream>

void Crawler::play()
{
  int intdummies[10];
  double ddummies[10];
  int playerLocation;
  int mpLocation;

  const int numberOfGames = 100;

  std::wstring action1;
  std::wstring action2;

  const std::vector<std::vector<int> >& paths = server->getPaths();

      server->StartGame();
      do {
	server->GetGameState(intdummies[0], playerLocation, 
			     intdummies[1], intdummies[2], ddummies[0], 
			     ddummies[1], ddummies[2]);
        mpLocation = 0; /* mplFinder()  */
        int size=paths[playerLocation].size();
        if(playerLocation = mpLocation)
          {
            action1='S'; /* we stand on the croc */
          }
        else
          {
            for(int i=0; i<size; i++ )  /* check all "grannar" efter mplocation */
              {
                if((paths[playerLocation][i]) = mpLocation)
                  {
                    action1=paths[playerLocation][i];
                  }          
                else
                  {
                    action1='S'; /* för trött för att tänka atm, fixa en bra shortest path till mpLocation */
                  }
                action2='S';
              }
          }
      } while(server->makeMove(action1, action2, finalScore));
}
