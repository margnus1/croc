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

    auto maxProbNode = max_element(begin(localPaths), localPaths.end(),
                                   [&](int m, int n){return probs[m-1]<probs[n-1];});
    int secondmax = *maxProbNode;
    localPaths.push_back(playerLocation);
    maxProbNode = max_element(begin(localPaths), localPaths.end(),
                              [&](int m, int n){return probs[m-1]<probs[n-1];});
    int max = *maxProbNode;
	
    if(max == playerLocation && probs[max-1] >0.0)
      {
	action1='S';
	action2=ToString(secondmax);
      }
    else 
      {
	//	int size = paths[playerLocation-1].size();
	//	int newnode = (long long)localPaths[rand()%size];
	//	action1 = ToString(newnode);
	action1=ToString(max);
	action2='S';
	/*	if(probs[max]<0.02){
		auto mrobNode = max_element(begin(paths[max-1]), paths[max-1].end(), [&](int m, int n){return probs[m]<probs[n];});
		int thirdmax = *mrobNode;
		action2=ToString(thirdmax);
		}*/
	//			if(probs[newnode-1]>0.2)
			      //	if(probs[newnode
	  /*	else{
	  size = paths[newnode-1].size();

	  newnode = (long long)paths[newnode-1][rand()%size];
	  action2 = ToString(newnode);
	  } */
      }

    if(action1[0] == 'S')
      probs[playerLocation-1]=0.0;
    if(action2[0] == 'S')
      probs[stoi(action1)-1]=0.0;
    //  Exception if action1 == action2 == 'S'
    //    			for( int i = 0; i <probs.size(); i++)
    //			  cout << setprecision(2) << setw(6) << probs[i];
    // cout << playerLocation<< endl;
    //		cout << backpacker1Activity << " " << backpacker2Activity << endl;
    //			cout << max << " " << secondmax << " " << playerLocation << endl;

  } while(server->makeMove(action1, action2, finalScore));
}
