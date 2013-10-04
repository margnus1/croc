#include "Crawler.h"
#include <vector>
#include <string>
#include <iostream>
#include "ToString.h"
#include <algorithm>
#include "markov.h"

using namespace std;
typedef vector<double> ProbList;
void Crawler::play()
{
  int score;
  int playerLocation;
  int backpacker1Activity;
  int backpacker2Activity;
  double calcium;
  double saline;
  double alkalinity;

  wstring action1;
  wstring action2;

  const vector<vector<int> >& paths = server->getPaths();
  const int noNodes = paths.size();

  vector<double> probs(noNodes, 1.0/noNodes); // probs[x] is the probability that the croc is in node x+1

  server->StartGame();
  Markov markov(*server);
  do {
    server->GetGameState(score, playerLocation, 
			 backpacker1Activity, backpacker2Activity, 
			 calcium, saline, alkalinity);
	
    vector<int> localPaths = paths[playerLocation-1];

    ProbList old = probs;
    markov.forward(old, probs);
    markov.considerWaterValues(probs, calcium, saline, alkalinity);
    markov.considerBackpacker(probs, backpacker1Activity);
    markov.considerBackpacker(probs, backpacker2Activity);
    markov.normalize(probs);

    /*    auto maxProbNode = max_element(begin(localPaths), localPaths.end(),
                                   [&](int m, int n){return probs[m-1]<probs[n-1];});
    int secondmax = *maxProbNode;
    localPaths.push_back(playerLocation);
    maxProbNode = max_element(begin(localPaths), localPaths.end(),
                              [&](int m, int n){return probs[m-1]<probs[n-1];});
                              int max = *maxProbNode; */

    int maximum = 1;
    double temp = probs[0];
    for (int i=0; i<probs.size(); i++) 
      if(temp<probs[i])
        {
          temp = probs[i];
          maximum = i + 1;
        }

    if(maximum == playerLocation)
      {
	action1='S';
	probs[playerLocation-1]=0.0;
	action2=ToString(dijkstra.next(playerLocation, maximum));
        // step to next node towards maximum using dijkstra
      }
    else 
      {
        int next = dijkstra.next(playerLocation, maximum);
	action1=ToString(next); // walk towards maximum
	if (probs[next-1] > 0.02) {
          // if there is 3% chance that cros is here(where we walked with action1) we test search
          action2='S';
	  probs[next-1]=0.0;
	  
	}
        else
          action2=ToString(dijkstra.next(next, maximum)); // walk a second time towards maximum
      }

  } while(server->makeMove(action1, action2, finalScore));
}
