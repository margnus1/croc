#include "CrocGame.h"
#include <iostream>
#include "Crawler.h"
#include "ProgressBar.h"
#include <cstring>
#include "console.h"
#include <iomanip>
#include <cmath>
#include <ctime>

int main(int argc, char *argv[]) {
  bool noob = false;
  CrocSession s(L"Group 4", noob);
  const int minNumberOfGames = 20;
  const int maxNumberOfGames = 200;
  const double faithInLuck = 20.0;
  long long total = 0;
  long long totalSquares = 0;
  long long count = 0;
  double bestAverage = 100000.0;
  time_t start = time(nullptr);
  Crawler crawler(&s);

  std::cout << std::endl << std::endl;
  do {
    // Play at least minNumberOfGames games, and up to
    // maxNumberOfGames, bailing when the average gets too bad
    for (int games = 0; games < minNumberOfGames ||
                        (games < maxNumberOfGames &&
                         (s.getAverage() / bestAverage) <
                         1.0 + (faithInLuck / games));
         games++) {
      crawler.play();

      total += crawler.finalScore;
      totalSquares += crawler.finalScore * crawler.finalScore;
      count++;

      if (games >= 100 && s.getAverage() < bestAverage) {
        s.PostResults();
        bestAverage = s.getAverage();
      }
    }

    double var = (double)(totalSquares - (total * total) / count) / count;
    Console::moveCursorUp(2);
    std::cout << std::setfill(' ') << std::setiosflags(std::ios::left)
              << "Avg: "    << std::setw(11) << ((double)total / count)
              << "StdDev: " << std::setw(8)  << std::sqrt(var)
              << "Best: "   << std::setw(10) << bestAverage
              << "    " // Because Windows
              << std::endl;
    std::cout << std::setfill(' ') << std::setiosflags(std::ios::left)
              << "Games: " << std::setw(9) << count
              << "Speed: " << std::setw(9) << count / difftime(time(nullptr), start)
              << "    " // Because Windows
              << std::endl;
    s.ClearRecord();
  } while (argc > 1 && strcmp(argv[1], "--forever") == 0);
}
