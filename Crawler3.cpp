#include "Crawler.h"
#include <vector>
#include <string>
#include <iostream>
#include "ToString.h"
#include <algorithm>

using namespace std;

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

  vector<double> probs; // probs[x] is the probability that the croc is in node x+1
  fill (probs.begin(), probs.begin()+noNodes, 1/noNodes);

      server->StartGame();
      do {
	server->GetGameState(score, playerLocation, 
			     backpacker1Activity, backpacker2Activity, 
			     calcium, saline, alkalinity);
	
	const vector<int> localPaths = paths[playerLocation];
	localPaths.push_back(playerLocation);

	auto maxProb = max_element(begin(localPaths), localPaths.end(), [&](int m, int n){return probs[m]<probs[n];});

	action2='S';

	if(*maxProb == playerLocation)
	  action1='S';
	else
	  {
	    localPaths.pop_back();
	    maxProb = max_element(begin(localPaths), localPaths.end(), [&](int m, int n){return probs[m]<probs[n];});
	    action1=ToString(*maxProb);
	  }
	if(action1[0] == 'S')
	  probs[playerLocation]=0.0;
	if(action2[0] == 'S')
	  probs[action2[0] -'0']=0.0;
	// Exception if action1 == action2 == 'S'
	
      } while(server->makeMove(action1, action2, finalScore));
}
