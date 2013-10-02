#include "CrocGame.h"
#include <iostream>
#include "Crawler.h"
#include "ProgressBar.h"

int main() {
  bool noob = false;
  CrocSession s(L"Group 4", noob);
  const int numberOfGames = 100;
  ProgressBar pb(numberOfGames, 80);

  Crawler crawler(&s);

  for(int i=0; i< numberOfGames; i++)
    {
      crawler.play();
      //      std::cout << "Game number: " << i+1 << "  \tScore: " << crawler.finalScore << std::endl;      
      pb.Tick();
    }

  s.PostResults();
  std::cout << "Number of games played: " << s.getPlayed() << std::endl;
  std::cout << "Avarage score: " << s.getAverage() << std::endl;
}


