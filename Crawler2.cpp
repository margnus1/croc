#include "Crawler.h"
#include <vector>
#include <string>
#include <iostream>

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

  int mpLocation;

  const std::vector<std::vector<int> >& paths = server->getPaths();

      server->StartGame();
      do {
        server->GetGameState(score, playerLocation,
                             backpacker1Activity, backpacker2Activity,
                             calcium, saline, alkalinity);

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
