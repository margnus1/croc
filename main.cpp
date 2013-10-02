#include "CrocGame.h"
#include <iostream>
#include "Crawler.h"
#include "ProgressBar.h"
#include <cstring>

int main(int argc, char *argv[]) {
  bool noob = false;
  CrocSession s(L"Group 4", noob);
  const int numberOfGames = 100;
  ProgressBar pb(numberOfGames, 80);
  double bestAverage = 100000.0;
  Crawler crawler(&s);

  do {
    int smin = 100000, smax = 0;
    for(int i=0; i< numberOfGames; i++)
      {
        crawler.play();
        //      std::cout << "Game number: " << i+1 << "  \tScore: " << crawler.finalScore << std::endl;
        smin = std::min(smin, crawler.finalScore);
        smax = std::max(smax, crawler.finalScore);
        pb.Tick();
      }

    std::cout << std::endl
              << "Avg: " << s.getAverage()
              << "\tMin: " << smin
              << "\tMax: " << smax
              << std::endl;
    if (s.getAverage() < bestAverage) {
      s.PostResults();
      bestAverage = s.getAverage();
    }
    s.ClearRecord();
  } while (argc > 1 && strcmp(argv[1], "--forever") == 0);
}


