#include "Crawler.h"
#include <vector>
#include <string>
#include <iostream>
#include "ToString.h"
#include <algorithm>
#include "Calc.cpp"

using namespace std;

namespace {
  void reactToBackpacker(vector<double> &probs, int bpactivity) {
    if(bpactivity<0)
      {
	for(int i=0; i<int(probs.size()); i++)
	  probs[i]=0.0;
	probs[-bpactivity-1]=1.0;
      }
    else if(bpactivity>0)
      probs[bpactivity-1]=0;
  }
}

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
  do {
    server->GetGameState(score, playerLocation, 
			 backpacker1Activity, backpacker2Activity, 
			 calcium, saline, alkalinity);
	
    vector<int> localPaths = paths[playerLocation-1];

    reactToBackpacker(probs, backpacker1Activity);
    reactToBackpacker(probs, backpacker2Activity);

    ProbList old = probs;
    calc(paths, old, probs);

    /*    auto maxProbNode = max_element(begin(localPaths), localPaths.end(),
                                   [&](int m, int n){return probs[m-1]<probs[n-1];});
    int secondmax = *maxProbNode;
    localPaths.push_back(playerLocation);
    maxProbNode = max_element(begin(localPaths), localPaths.end(),
                              [&](int m, int n){return probs[m-1]<probs[n-1];});
                              int max = *maxProbNode; */

    int maximum = 0;
    double temp = probs[0];
    for (int i=0; i<probs.size(); i++) 
      if(temp<probs[i])
        {
          temp = probs[i];
          maximum = i;
        }

  if(maximum == playerLocation)
    {
      action1='S';
	action2=ToString(dijkstra.next(playerLocation,maximum));
        // step to next node towards maximum using dijkstra
      }
    else 
      {
        int next = dijkstra.next(playerLocation,maximum)
          action1=ToString(next); // walk towards maximum
        if (probs(next) > 0.69)
          // if there is 70% chance that cros is here(where we walked with action1) we test search
          action2='S';
        else
          action2=ToString(dijkstra.next(next,maximum)) // walk a second time towards maximum
	
            }

    if(action1[0] == 'S')
      probs[playerLocation-1]=0.0;
    if(action2[0] == 'S')
      probs[stoi(action1)-1]=0.0;

  } while(server->makeMove(action1, action2, finalScore));
}
