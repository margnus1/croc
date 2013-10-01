#include "CrocGame.h"
#include <cassert>
#include <random>
#include <chrono>

class http_pImple {};

static int const GRAPH_SIZE = 35;
static std::vector<std::vector<int> > graph;

class CrocGame {
public:
  struct Waterhole {
  public:
    std::normal_distribution<double> calciumDistribution,
      salinityDistribution, alkalinityDistribution;
  };

  CrocGame()
    : waterholes(GRAPH_SIZE),
      finished(false)
  {
    //    generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<double> mean(1.0, 3.0),
      deviation(0.1, 2.0);
    for (int n = 0; n < int(graph.size()); n++) {
      waterholes[n].calciumDistribution    = std::normal_distribution<double>(mean(generator), deviation(generator));
      waterholes[n].salinityDistribution   = std::normal_distribution<double>(mean(generator), deviation(generator));
      waterholes[n].alkalinityDistribution = std::normal_distribution<double>(mean(generator), deviation(generator));
    }
  }

  void updateReadings () {
    calciumReading    = waterholes[crocLocation-1].calciumDistribution(generator);
    salinityReading   = waterholes[crocLocation-1].salinityDistribution(generator);
    alkalinityReading = waterholes[crocLocation-1].alkalinityDistribution(generator);
  }

  void randomWalk (int &entity_position) {
    std::uniform_int_distribution<int> dist(0, graph[entity_position - 1].size());
    entity_position = graph[entity_position - 1][dist(generator)];
  }

  void playerMove(std::wstring move) {
    if (move == L"S") {
      if (playerLocation == crocLocation) finished = true;
    } else {
      int neighbor = std::stoi(move);
      bool isNeighbor = false;
      for (int i = 0; i < int(graph[playerLocation - 1].size()); i++)
        if (graph[playerLocation - 1][i] == neighbor) isNeighbor = true;
      if (isNeighbor) playerLocation = neighbor;
    }
  }

  void moveBackpacker(int &activity) {
    if (activity < 0) activity = 0;
    else if (activity > 0) {
      randomWalk(activity);
      if (activity == crocLocation)
        activity = -activity;
    }
  }

  void tick() {
    randomWalk(crocLocation);
    moveBackpacker(backpacker1Activity);
    moveBackpacker(backpacker2Activity);
    updateReadings();
  }

  std::default_random_engine generator;

  std::vector<Waterhole> waterholes;

  bool finished;
  int crocLocation;
  int playerLocation;
  int backpacker1Activity, backpacker2Activity;
  double calciumReading, salinityReading, alkalinityReading;
};

CrocSession::CrocSession(const std::wstring& GroupName, bool &OK) {
  graph = std::vector<std::vector<int> >(GRAPH_SIZE);
  graph[0].push_back(2); graph[0].push_back(17);
  graph[1].push_back(1); graph[1].push_back(3); graph[1].push_back(15); graph[1].push_back(17);
  graph[2].push_back(2); graph[2].push_back(4); graph[2].push_back(13); graph[2].push_back(15);
  graph[3].push_back(3); graph[3].push_back(5); graph[3].push_back(12);
  graph[4].push_back(4); graph[4].push_back(6); graph[4].push_back(12);
  graph[5].push_back(5); graph[5].push_back(7); graph[5].push_back(8); graph[5].push_back(12);
  graph[6].push_back(6); graph[6].push_back(8);
  graph[7].push_back(6); graph[7].push_back(7); graph[7].push_back(9);
  graph[8].push_back(8); graph[8].push_back(10); graph[8].push_back(28);
  graph[9].push_back(9); graph[9].push_back(11); graph[9].push_back(28); graph[9].push_back(29);
  graph[10].push_back(10); graph[10].push_back(12); graph[10].push_back(31);
  graph[11].push_back(4); graph[11].push_back(5); graph[11].push_back(6); graph[11].push_back(11); graph[11].push_back(13);
  graph[12].push_back(3); graph[12].push_back(12); graph[12].push_back(14);
  graph[13].push_back(13); graph[13].push_back(15); graph[13].push_back(33);
  graph[14].push_back(2); graph[14].push_back(3); graph[14].push_back(14); graph[14].push_back(16);
  graph[15].push_back(15); graph[15].push_back(17); graph[15].push_back(20); graph[15].push_back(35);
  graph[16].push_back(1); graph[16].push_back(2); graph[16].push_back(16); graph[16].push_back(18);
  graph[17].push_back(17); graph[17].push_back(19); graph[17].push_back(20);
  graph[18].push_back(18); graph[18].push_back(20); graph[18].push_back(21);
  graph[19].push_back(16); graph[19].push_back(18); graph[19].push_back(19); graph[19].push_back(21); graph[19].push_back(35);
  graph[20].push_back(19); graph[20].push_back(20); graph[20].push_back(22); graph[20].push_back(23);
  graph[21].push_back(21); graph[21].push_back(23); graph[21].push_back(34); graph[21].push_back(35);
  graph[22].push_back(21); graph[22].push_back(22); graph[22].push_back(24);
  graph[23].push_back(23); graph[23].push_back(25); graph[23].push_back(34); graph[23].push_back(35);
  graph[24].push_back(24); graph[24].push_back(26); graph[24].push_back(32); graph[24].push_back(34);
  graph[25].push_back(25); graph[25].push_back(27); graph[25].push_back(29); graph[25].push_back(30); graph[25].push_back(32);
  graph[26].push_back(26); graph[26].push_back(28); graph[26].push_back(29); graph[26].push_back(30);
  graph[27].push_back(9); graph[27].push_back(10); graph[27].push_back(27); graph[27].push_back(29);
  graph[28].push_back(10); graph[28].push_back(26); graph[28].push_back(27); graph[28].push_back(28); graph[28].push_back(30);
  graph[29].push_back(26); graph[29].push_back(29); graph[29].push_back(31); graph[29].push_back(32);
  graph[30].push_back(11); graph[30].push_back(30); graph[30].push_back(32); graph[30].push_back(33);
  graph[31].push_back(25); graph[31].push_back(26); graph[31].push_back(30); graph[31].push_back(31); graph[31].push_back(33); graph[31].push_back(34);
  graph[32].push_back(14); graph[32].push_back(31); graph[32].push_back(32); graph[32].push_back(34);
  graph[33].push_back(22); graph[33].push_back(24); graph[33].push_back(25); graph[33].push_back(32); graph[33].push_back(33); graph[33].push_back(35);
  graph[34].push_back(16); graph[34].push_back(20); graph[34].push_back(22); graph[34].push_back(24); graph[34].push_back(34);

  Group = GroupName;
  OK = true;
};

CrocSession::~CrocSession() {
  if (Game != nullptr) delete Game;
};

int CrocSession::getPlayed() const { return 0; };

//  Get your session statistics
//  -   You are ranked on your average, and lower is better.
double CrocSession::getAverage () const { return 0.0; };

//  Clear the session statistics
void CrocSession::ClearRecord() {};

//  Submit session statistics to the server
//  -   Requires that you have played at least 100 games.
void CrocSession::PostResults() const {};

//  Start a game
//  -   The previous game must have finished
void CrocSession::StartGame () {
  assert(Game == nullptr || Game->finished);
  if (Game != nullptr) delete Game;
  Game = new CrocGame();
};

//  Get Paths
//  -   These remain constant from game to game
const std::vector<std::vector<int> >& CrocSession::getPaths () const {
  return graph;
};

//  Make moves
//  -   Note that you move twice for every move Croc and the backpackers make. So you can move to a square and search it before Croc moves on.
//  -   Valid moves are:
//      i.  The index of a waterhole to travel to.
//          (It must be reachable from your current location)
//      ii. 'S', indicating that the waterhole should be search for Croc.
//  -   Invalid moves will mean you do nothing.
// Return false if the croc is found, true otherwise.
bool CrocSession::makeMove (const std::wstring& playerMove,
                            const std::wstring& playerMove2,
                            int& outScore) {
  return false;
};

//  Get the current game state
//  -   Shows location of yourself and backpackers, and readings from Croc's sensors.
//  -   Backpacker locations are 0 if they are eaten, and multipled by -1 if they are being eaten.
//  -   Starting locations are different each game.
void CrocSession::GetGameState (int& score,
                                int& playerLocation,
                                int& backpacker1Activity,
                                int& backpacker2Activity,
                                double& calciumReading,
                                double& salineReading,
                                double& alkalinityReading) const {
  assert(Game != nullptr);
  score = this->score;
  playerLocation = Game->playerLocation;
  backpacker1Activity = Game->backpacker1Activity;
  backpacker2Activity = Game->backpacker2Activity;
  calciumReading = Game->calciumReading;
  salineReading = Game->salinityReading;
  alkalinityReading = Game->alkalinityReading;
};

//  Get the game distributions
//  -   Means and standard deviations of calcium, salinity and alkalinity
//distributions for each waterhole.
//  -   These are different each game.
void CrocSession::GetGameDistributions (
                           std::vector<std::pair<double,double> >& calcium, // For each waterhole:  mean, std dev
                           std::vector<std::pair<double,double> >& salinity, // For each waterhole:  mean, std dev
                           std::vector<std::pair<double,double> >& alkalinity // For each waterhole: mean, std dev
                           ) const {
  assert(Game != nullptr);
  calcium.resize(GRAPH_SIZE);
  salinity.resize(GRAPH_SIZE);
  alkalinity.resize(GRAPH_SIZE);
  for (int i = 0; i < GRAPH_SIZE; i++) {
    calcium[i] = std::pair<double, double>
      (Game->waterholes[i].calciumDistribution.mean(),
       Game->waterholes[i].calciumDistribution.stddev());
    salinity[i] = std::pair<double, double>
      (Game->waterholes[i].salinityDistribution.mean(),
       Game->waterholes[i].salinityDistribution.stddev());
    alkalinity[i] = std::pair<double, double>
      (Game->waterholes[i].alkalinityDistribution.mean(),
       Game->waterholes[i].alkalinityDistribution.stddev());
  }
};
