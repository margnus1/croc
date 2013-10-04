#include "markov.h"
#include <iostream>
#include <cassert>
#include <cmath>

using namespace std;

typedef vector<vector<int> > Graph;
typedef vector<double> ProbList;
typedef vector<pair<double, double> > WaterDistribution;

const double tau = 6.283185307179586476925286766559;
const double sqrttau = sqrt(tau);

Markov::Markov(const CrocSession &session) :
  graph(session.getPaths()),
  calciumDist(),
  salinityDist(),
  alkalinityDist() {
  session.GetGameDistributions(calciumDist, salinityDist, alkalinityDist);
}

void Markov::forward(const ProbList &oldList, ProbList &list)
  {
    assert(&oldList != &list);
    //  cout << oldList.size() << " " << list.size() << endl;
    for(int i=0; i<int(graph.size()); i++)
      {
        const int n = graph[i].size();
        list[i]=oldList[i]/(n+1);
        for(int j=0; j<n; j++)
          {
            const int m=graph[graph[i][j]-1].size();
            //cout << "i: " << i << " j: " << j << " m: " << m << endl;
            const int c = graph[i][j];
            //	  cout << "c: " << c << endl;
            const double op = oldList[c-1];
            //	  cout << "op: " << op << endl;

            list[i]+=op/(m+1);
            //	  cout << "list[i]: " << list[i] << endl;
	    assert(list[i]>=0.0 && list[i]<=1.0);
          }
      }
    double sum = 0.0;
    for (int i = 0; i < int(list.size()); i++) sum += list[i];
    assert(abs(1.0 - sum) < 0.000001);
  }

void Markov::normalize(ProbList &list) {
  double sum = 0.0;
  for (int i = 0; i < int(list.size()); i++) sum += list[i];
  assert(sum > 0.0);
  double factor = 1.0/sum;
  for (int i = 0; i < int(list.size()); i++)
    list[i] *= factor;
}

void Markov::considerBackpacker(ProbList &list, int activity) {
  if(activity<0) {
    for(int i=0; i<int(list.size()); i++)
      list[i]=0.0;
    list[-activity-1]=1.0;
  } else if(activity>0)
    list[activity-1]=0;
}

namespace {
  double normalPdf(pair<double, double> dist, double x) {
    return 1.0 / (sqrttau * dist.second) *
      exp(- (x - dist.first) * (x - dist.first) /
            (2 * dist.second * dist.second));
  }
}

void Markov::considerWaterValues(ProbList &list, double calcium,
                                 double saline, double alkalinity) {
  for (int i = 0; i < int(list.size()); i++)
    list[i] *= normalPdf(calciumDist[i],    calcium) *
               normalPdf(salinityDist[i],   saline)  *
               normalPdf(alkalinityDist[i], alkalinity);
}
