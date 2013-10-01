#include "CrocGame.h"


class http_pImple {};

class CrocGame {
public:
  CrocGame() {
    graph = std::vector<std::vector<int> >(35);
    graph[0][0] = 2;
    graph[0][1] = 17;
    graph[1][0] = 1;
    graph[1][1] = 3;
    graph[1][2] = 15;
    graph[1][3] = 17;
    graph[2][0] = 2;
    graph[2][1] = 4;
    graph[2][2] = 13;
    graph[2][3] = 15;
    graph[3][0] = 3;
    graph[3][1] = 5;
    graph[3][2] = 12;
    graph[4][0] = 4;
    graph[4][1] = 6;
    graph[4][2] = 12;
    graph[5][0] = 5;
    graph[5][1] = 7;
    graph[5][2] = 8;
    graph[5][3] = 12;
    graph[6][0] = 6;
    graph[6][1] = 8;
    graph[7][0] = 6;
    graph[7][1] = 7;
    graph[7][2] = 9;
    graph[8][0] = 8;
    graph[8][1] = 10;
    graph[8][2] = 28;
    graph[9][0] = 9;
    graph[9][1] = 11;
    graph[9][2] = 28;
    graph[9][3] = 29;
    graph[10][0] = 10;
    graph[10][1] = 12;
    graph[10][2] = 31;
    graph[11][0] = 4;
    graph[11][1] = 5;
    graph[11][2] = 6;
    graph[11][3] = 11;
    graph[11][4] = 13;
    graph[12][0] = 3;
    graph[12][1] = 12;
    graph[12][2] = 14;
    graph[13][0] = 13;
    graph[13][1] = 15;
    graph[13][2] = 33;
    graph[14][0] = 2;
    graph[14][1] = 3;
    graph[14][2] = 14;
    graph[14][3] = 16;
    graph[15][0] = 15;
    graph[15][1] = 17;
    graph[15][2] = 20;
    graph[15][3] = 35;
    graph[16][0] = 1;
    graph[16][1] = 2;
    graph[16][2] = 16;
    graph[16][3] = 18;
    graph[17][0] = 17;
    graph[17][1] = 19;
    graph[17][2] = 20;
    graph[18][0] = 18;
    graph[18][1] = 20;
    graph[18][2] = 21;
    graph[19][0] = 16;
    graph[19][1] = 18;
    graph[19][2] = 19;
    graph[19][3] = 21;
    graph[19][4] = 35;
    graph[20][0] = 19;
    graph[20][1] = 20;
    graph[20][2] = 22;
    graph[20][3] = 23;
    graph[21][0] = 21;
    graph[21][1] = 23;
    graph[21][2] = 34;
    graph[21][3] = 35;
    graph[22][0] = 21;
    graph[22][1] = 22;
    graph[22][2] = 24;
    graph[23][0] = 23;
    graph[23][1] = 25;
    graph[23][2] = 34;
    graph[23][3] = 35;
    graph[24][0] = 24;
    graph[24][1] = 26;
    graph[24][2] = 32;
    graph[24][3] = 34;
    graph[25][0] = 25;
    graph[25][1] = 27;
    graph[25][2] = 29;
    graph[25][3] = 30;
    graph[25][4] = 32;
    graph[26][0] = 26;
    graph[26][1] = 28;
    graph[26][2] = 29;
    graph[26][3] = 30;
    graph[27][0] = 9;
    graph[27][1] = 10;
    graph[27][2] = 27;
    graph[27][3] = 29;
    graph[28][0] = 10;
    graph[28][1] = 26;
    graph[28][2] = 27;
    graph[28][3] = 28;
    graph[28][4] = 30;
    graph[29][0] = 26;
    graph[29][1] = 29;
    graph[29][2] = 31;
    graph[29][3] = 32;
    graph[30][0] = 11;
    graph[30][1] = 30;
    graph[30][2] = 32;
    graph[30][3] = 33;
    graph[31][0] = 25;
    graph[31][1] = 26;
    graph[31][2] = 30;
    graph[31][3] = 31;
    graph[31][4] = 33;
    graph[31][5] = 34;
    graph[32][0] = 14;
    graph[32][1] = 31;
    graph[32][2] = 32;
    graph[32][3] = 34;
    graph[33][0] = 22;
    graph[33][1] = 24;
    graph[33][2] = 25;
    graph[33][3] = 32;
    graph[33][4] = 33;
    graph[33][5] = 35;
    graph[34][0] = 16;
    graph[34][1] = 20;
    graph[34][2] = 22;
    graph[34][3] = 24;
    graph[34][4] = 34;
  }

  std::vector<std::vector<int> > graph;

};

CrocSession::CrocSession(const std::wstring& GroupName, bool &OK)  {
  Group = GroupName;
  Game = new CrocGame();
  OK = true;
};

CrocSession::~CrocSession() { delete Game; };

int CrocSession::getPlayed() const { return 0; };

//  Get your session statistics
//  -   You are ranked on your average, and lower is better.
double CrocSession::getAverage () const {return 0.0;};

//  Clear the session statistics
void CrocSession::ClearRecord() {};

//  Submit session statistics to the server
//  -   Requires that you have played at least 100 games.
void CrocSession::PostResults() const {};

//  Start a game
//  -   The previous game must have finished
void CrocSession::StartGame () {};

//  Get Paths
//  -   These remain constant from game to game
const std::vector<std::vector<int> >& CrocSession::getPaths () const {
  return Game->graph;
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
                            int& outScore) { return false; };

//  Get the current game state
//  -   Shows location of yourself and backpackers, and readings from Croc's sensors.
//  -   Backpacker locations are 0 if they are eaten, and multipled by -1 if they are being eaten.
//  -   Starting locations are different each game.
void CrocSession::GetGameState (
                                int& score,
                                int& playerLocation,
                                int& backpacker1Activity,
                                int& backpacker2Activity,
                                double& calciumReading,
                                double& salineReading,
                                double& alkalinityReading
                                ) const {};

//  Get the game distributions
//  -   Means and standard deviations of calcium, salinity and alkalinity
//distributions for each waterhole.
//  -   These are different each game.
void CrocSession::GetGameDistributions (
                           std::vector<std::pair<double,double> >& calcium, // For each waterhole:  mean, std dev
                           std::vector<std::pair<double,double> >& salinity, // For each waterhole:  mean, std dev
                           std::vector<std::pair<double,double> >& alkalinity // For each waterhole: mean, std dev
                           ) const {};
