#include "Crawler.h"
#include <vector>
#include <string>
#include <iostream>
#include "ToString.h"
#include <algorithm>
#include "Calc.cpp"

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

  for(int i=0; i<noNodes; i++)
    probs.push_back(1.0/noNodes);

  server->StartGame();
  do {
    server->GetGameState(score, playerLocation, 
			 backpacker1Activity, backpacker2Activity, 
			 calcium, saline, alkalinity);
	
    vector<int> localPaths;
    localPaths = paths[playerLocation-1];

    if(backpacker1Activity<0)
      {
	for(int i=0; i<noNodes; i++)
	  probs[i]=0.0;
	probs[-1-backpacker1Activity]=1.0;
      }
    else if(backpacker1Activity>0)
      probs[backpacker1Activity-1]=0;

    if(backpacker2Activity<0)
      {
	for(int i=0; i<noNodes; i++)
	  probs[i]=0.0;
	probs[-1-backpacker2Activity]=1.0; 
      }
    else if(backpacker2Activity>0)
      probs[backpacker2Activity-1]=0;

    ProbList old = probs;
    calc(paths, old, probs);




    auto maxProbNode = max_element(begin(localPaths), localPaths.end(), [&](int m, int n){return probs[m]<probs[n];});
    int secondmax = *maxProbNode;
    localPaths.push_back(playerLocation-1);
    maxProbNode = max_element(begin(localPaths), localPaths.end(), [&](int m, int n){return probs[m]<probs[n];});
    int max = *maxProbNode;
	
    if(max == playerLocation && probs[max] >0.0)
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
