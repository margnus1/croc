#include "CrocGame.h"


class http_pImple {};

class CrocGame {
public:
  
  
};

CrocSession::CrocSession(const std::wstring& GroupName, bool &OK)  {
  Group = GroupName;
  OK = true;
};

CrocSession::~CrocSession() {};

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
  return std::vector<std::vector<int> > ();
};


    //  Make moves
    //  -   Note that you move twice for every move Croc and the backpackers make. So you can move to a square and search it before Croc moves on.
    //  -   Valid moves are:
    //      i.  The index of a waterhole to travel to.
    //          (It must be reachable from your current location)
    //      ii. 'S', indicating that the waterhole should be search for Croc.
    //  -   Invalid moves will mean you do nothing.
    // Return false if the croc is found, true otherwise.
    bool CrocSession::makeMove (
        const std::wstring& playerMove,
        const std::wstring& playerMove2,
        int& outScore) {};

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
