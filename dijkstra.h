#include <vector>

// Represents a precomputed dijkstra from each node
class Dijkstra {
 public:
  Dijkstra(const std::vector<std::vector<int> > &graph);
  // The optimal next step if I am in from and want to reach to
  int next(int from, int to) const;
 private:
  typedef unsigned char byte;
  byte &next(int from, int to);
  int size;
  std::vector<byte> parents;
};
