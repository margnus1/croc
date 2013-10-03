#include "CrocGame.h"
#include <iostream>
#include "Crawler.h"
#include "ProgressBar.h"
#include <cstring>
#include "console.h"
#include <iomanip>

int main(int argc, char *argv[]) {
  bool noob = false;
  CrocSession s(L"Group 4", noob);
  const int numberOfGames = 100;
  //  ProgressBar pb(numberOfGames, 80);
  double avgSum = 0.0;
  double bestAverage = 100000.0;
  int count = 0;
  Crawler crawler(&s);

  std::cout << std::endl;
  do {
    int smin = 100000, smax = 0;
    for(int i=0; i< numberOfGames; i++)
      {
        crawler.play();
        //      std::cout << "Game number: " << i+1 << "  \tScore: " << crawler.finalScore << std::endl;
        smin = std::min(smin, crawler.finalScore);
        smax = std::max(smax, crawler.finalScore);
        //    pb.Tick();
      }


    Console::moveCursorUp(1);
    count++;
    avgSum += s.getAverage();
    std::cout << std::setfill(' ') << std::setiosflags(std::ios::left)
              << "Last Avg: " << std::setw(8) << s.getAverage()
              << "Cum Avg: "  << std::setw(8) << (avgSum / count)
              << "Best Avg: " << std::setw(8) << bestAverage
              << "    " // Because Windows
              << std::endl;
    if (s.getAverage() < bestAverage) {
      s.PostResults();
      bestAverage = s.getAverage();
    }
    s.ClearRecord();
  } while (argc > 1 && strcmp(argv[1], "--forever") == 0);
}


