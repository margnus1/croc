#include <vector>
#include <iostream>
#include <cassert>

using namespace std;

typedef vector<vector<int> > Graph;
typedef vector<double> ProbList;



void calc(const Graph &G, const ProbList &oldList, ProbList &list)
{
  assert(&oldList != &list);
  //  cout << oldList.size() << " " << list.size() << endl;
  for(int i=0; i<int(G.size()); i++)
    {
      const int n = G[i].size();
      list[i]=oldList[i]/(n+1);
      for(int j=0; j<n; j++)
	{
	  const int m=G[G[i][j]-1].size();
	  //cout << "i: " << i << " j: " << j << " m: " << m << endl;
	  const int c = G[i][j];
	  //	  cout << "c: " << c << endl;
	  const double op = oldList[c-1];
	  //	  cout << "op: " << op << endl;

	  list[i]+=op/(m+1);
	  //	  cout << "list[i]: " << list[i] << endl;
	}
    }
}
