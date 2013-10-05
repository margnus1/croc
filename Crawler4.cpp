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
    markov.normalize(probs);
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
    vector<int> tempvector(paths.size(), 0);
    
    for(int i=0; i<paths.size(); i++)
      {
	tempvector[i]=10*probs[i];
	for(int j=0; j<paths[i].size(); j++)
	  tempvector[i] += probs[paths[i][j]-1];
      }
    
    double temp = tempvector[0];
    for (int i=0; i<tempvector.size(); i++) 
      if(temp<tempvector[i])
        {
          temp = tempvector[i];
          maximum = i + 1;
        }

    int maximum2 = 1;
    temp=0;
    for (int i=0; i<probs.size(); i++) 
      if(temp<probs[i])
        {
          temp = probs[i];
          maximum2 = i + 1;
        }

    if(playerLocation == maximum2)
      {
      maximum = maximum2;
      }
    else
    for(int i=0; i<paths[playerLocation-1].size(); i++)
      if(maximum2 == paths[playerLocation-1][i])
	{
	  maximum=maximum2;
	  break;
	  cout << "kuk";
	}

    if(maximum == playerLocation)
      {
	action1='S';
	probs[playerLocation-1]=0.0;
	maximum = 1;
	temp=0;
	// Calculate new maximum
	for (int i=0; i<probs.size(); i++) 
	  if(temp<probs[i])
	    {
	      temp = probs[i];
	      maximum = i + 1;
	    }

	int next = dijkstra.next(playerLocation, maximum);
	// Tiebreak
	if(next!=maximum)
	  {
	    int next2 = dijkstra.next(next, maximum);
	    vector<int> commonNeighbours;
	    vector<int> plLoc = paths[playerLocation-1];
	    vector<int> nxt = paths[next2-1];
	    for(int i=0; i< plLoc.size(); i++)
	      for(int j=0; j<nxt.size(); j++)
		if(plLoc[i]==nxt[j])
		  commonNeighbours.push_back(plLoc[i]);

	    temp = 0;
	    next2 = commonNeighbours[0];
	    // Tiebreak number of paths first
	    /*	    for(int i=0; i<commonNeighbours.size(); i++)
	      {
		if(paths[commonNeighbours[i]-1].size()>temp || 
		   (paths[commonNeighbours[i]-1].size()==temp &&
		    probs[commonNeighbours[i]-1] > probs[next2-1]))
		  {
		    temp = paths[commonNeighbours[i]-1].size();
		    next2 = commonNeighbours[i];
		  } 
		  } */

	    // Tiebreak probability first
	    for(int i=0; i<commonNeighbours.size(); i++)
	      {
		if(paths[commonNeighbours[i]-1].size()>temp || 
		   (paths[commonNeighbours[i]-1].size()==temp &&
		    probs[commonNeighbours[i]-1] > probs[next2-1]))
		  {
		    temp = paths[commonNeighbours[i]-1].size();
		    next2 = commonNeighbours[i];
		  } 
	      }
	    //	    cout << next << " " << next2 << endl; 
	    	    next = next2;
	  } 
	action2=ToString(next);
      }
    else 
      {
        int next = dijkstra.next(playerLocation, maximum);

	// Tiebreak
	if(next!=maximum)
	  {
	    int next2 = dijkstra.next(next, maximum);
	    vector<int> commonNeighbours;
	    vector<int> plLoc = paths[playerLocation-1];
	    vector<int> nxt = paths[next2-1];
	    for(int i=0; i< plLoc.size(); i++)
	      for(int j=0; j<nxt.size(); j++)
		if(plLoc[i]==nxt[j])
		  commonNeighbours.push_back(plLoc[i]);

	    temp = 0;
	    double dtemp = 0;
	    next2 = commonNeighbours[0];

	    // Tiebreak number of paths first
	    for(int i=0; i<commonNeighbours.size(); i++)
	      {
		if(paths[commonNeighbours[i]-1].size()>temp || 
		   (paths[commonNeighbours[i]-1].size()==temp &&
		    probs[commonNeighbours[i]-1] > probs[next2-1]))
		  {
		    temp = paths[commonNeighbours[i]-1].size();
		    next2 = commonNeighbours[i];
		  } 
	      }

	    // Tiebreak probability first
	    /*	    for(int i=0; i<commonNeighbours.size(); i++)
	      {
		if(probs[commonNeighbours[i]-1] > dtemp ||
                   (probs[commonNeighbours[i]-1] == dtemp &&
                    paths[commonNeighbours[i]-1].size() > paths[next2-1].size()))
		  {
		    dtemp = probs[commonNeighbours[i]-1];
		    next2 = commonNeighbours[i];
		  } 
		  } */
	    //	    cout << next << " " << next2 << endl; 
	    	    next = next2;
	    } 

	action1=ToString(next); // walk towards maximum
	if (probs[next-1] > 0.02) {
          // if there is 2% chance that cros is here(where we walked with action1) we test search
          action2='S';
	  probs[next-1]=0.0;
	  
	}
        else 
	  {
	    
          next = dijkstra.next(next, maximum); // walk a second time towards maximum
	  
	  // This tiebreaker segfaults during dijkstras for some fucked up reason
	  /*  if(next!=maximum)
	    {
	      int next2 = dijkstra.next(next, maximum);
	      vector<int> commonNeighbours;
	      vector<int> plLoc = paths[playerLocation-1];
	      vector<int> nxt = paths[next2-1];
	      for(int i=0; i< plLoc.size(); i++)
		for(int j=0; j<nxt.size(); j++)
		  if(plLoc[i]==nxt[j])
		    commonNeighbours.push_back(plLoc[i]);
	      temp = 0;
	      next2 = commonNeighbours[0];
	      for(int i=0; i<commonNeighbours.size(); i++)
		{
		  if(paths[commonNeighbours[i]-1].size()>temp || 
		     (paths[commonNeighbours[i]-1].size()==temp &&
		      probs[commonNeighbours[i]-1] > probs[next2-1]))
		    {
		      temp = paths[commonNeighbours[i]-1].size();
		      next2 = commonNeighbours[i];
		    } 
		}

		// Tiebreak probability first                                                                                                            double dtemp = 0;
		/*      for(int i=0; i<commonNeighbours.size(); i++)                                                                                     
              {                                                                                                                                                     if(probs[commonNeighbours[i]-1] > dtemp ||                                                                                                             (probs[commonNeighbours[i]-1] == dtemp &&                                                                                                             paths[commonNeighbours[i]-1].size() > paths[next2-1].size()))                                                                                     {                                                                                                                                  
                  dtemp = probs[commonNeighbours[i]-1];                                                                                            
                    next2 = commonNeighbours[i];                                                                                                     
               }                                                                                                                                  
	      //	    cout << next << " " << next2 << endl; 
	      	    next = next2;
		    } */
	  action2=ToString(next);
	  }
      }
      } while(server->makeMove(action1, action2, finalScore));
  }
