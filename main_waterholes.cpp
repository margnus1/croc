#include "CrocGame.h"
#include "ToString.h"
#include <iostream>
#include <iomanip>

int main() {
  bool noob = false;
  CrocSession s(L"Group 4", noob);
  const int rounds = 100;

  s.StartGame();
  std::vector<std::pair<double, double> > calc, sal, alk;
  s.GetGameDistributions(calc, sal, alk);
  std::cout << "Hole\tCalc\t\tSal\t\tAlk" << std::endl;
  for (int i = 0; i < 35; i++) {
    std::cout << std::setprecision(7) << i + 1 << "\t"
              << calc[i].first << "\t" << calc[i].second << "\t"
              << sal[i].first  << "\t" << sal[i].second  << "\t"
              << alk[i].first  << "\t" << alk[i].second  << "\t"
              << std::endl;
  }

  std::cout << std::endl << "player\tbp1\tbp2\tcal\tsal\talk" << std::endl;

  for (int i = 0; i < rounds; i++) {
      int score, playerLocation, backpacker1Activity, backpacker2Activity;
      double calciumReading, salineReading, alkalinityReading;
      s.GetGameState(score, playerLocation, backpacker1Activity, backpacker2Activity,
          calciumReading, salineReading, alkalinityReading);

      std::cout << std::setprecision(6)
          << playerLocation       << "\t" << backpacker1Activity << "\t"
          << backpacker2Activity  << "\t" << calciumReading      << "\t"
          << salineReading        << "\t" << alkalinityReading   << "\t"
          << std::endl;

      s.makeMove(ToString(playerLocation), ToString(playerLocation), score);
  }

  std::cout << "Number of games played: " << s.getPlayed() << std::endl;
}


