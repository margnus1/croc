#include "Crawler.h"
#include <vector>
#include <string>
#include <iostream>
#include "ToString.h"
#include <algorithm>

using namespace std;

void fix(double &p) { int d = p-0.5; p+=d/10.0;};
//void fix(double &p) { if (p<0.1) p+=0.1; p*=1/(p+0.5);};
void pr(double p) { cout << p << endl; }

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
  //  const int noNodes = paths.size();

  //  vector<double> probs; // probs[x] is the probability that the croc is in node x+1

  //  for(int i=0; i<noNodes; i++)
  // probs.push_back(0.5);

      server->StartGame();
      do {
	server->GetGameState(score, playerLocation, 
			     backpacker1Activity, backpacker2Activity, 
			     calcium, saline, alkalinity);
	
	/*	vector<int> localPaths;
	localPaths = paths[playerLocation-1];
	//	localPaths.push_back(playerLocation-1);

	for_each(probs.begin(), probs.end(), &fix);

	auto maxProbNode = min_element(begin(localPaths), localPaths.end(), [&](int m, int n){return probs[m]<probs[n];});
	int max = *maxProbNode;
	//	localPaths.pop_back();
	maxProbNode = max_element(begin(localPaths), localPaths.end(), [&](int m, int n){return probs[m]<probs[n];});
	int secondmax = *maxProbNode;


	if(backpacker1Activity<0)
	  probs[1-backpacker1Activity]=1.0;
	if(backpacker2Activity<0)
	probs[1-backpacker2Activity]=1.0; */

	/*	if(max == playerLocation)
	  {
	    action1='S';
	    action2=ToString(secondmax);
	  }
	  else */
	  
	int size = paths[playerLocation-1].size();
	action1=ToString((long long)paths[playerLocation-1][rand()%size]-1);
	action2='S';
	     

	/*	if(action1[0] == 'S')
	  probs[playerLocation-1]=0.01;
	if(action2[0] == 'S')
	probs[action2[0] -'0'-1]=0.01;*/
	//  Exception if action1 == action2 == 'S'
	//	for( std::vector<double>::const_iterator i = probs.begin(); i != probs.end(); ++i)
	//  cout << *i << ' ';
	cout << playerLocation<< endl;

      } while(server->makeMove(action1, action2, finalScore));
}
