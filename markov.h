#pragma once

#include <vector>
#include "CrocGame.h"

class Markov {
 public:
  typedef std::vector<double> ProbList;

  Markov(const CrocSession &session);
  void forward(const std::vector<double> &oldList,
                     std::vector<double> &list);
  void normalize(std::vector<double> &list);
  void considerWaterValues(std::vector<double> &list, double calcium,
                           double saline, double alkalinity);
  void considerBackpacker(std::vector<double> &list, int activity);
 private:
  const std::vector<std::vector<int> > &graph;
  std::vector<std::pair<double, double> >
    calciumDist,
    salinityDist,
    alkalinityDist;
};
