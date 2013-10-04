#include <vector>

// Represents a precomputed dijkstra from each node
class Dijkstra {
 public:
  Dijkstra(const std::vector<std::vector<int> > &graph);
  // The optimal next step if I am in from and want to reach to
  int next(int to, int from) const;
 private:
  typedef unsigned char byte;
  byte &next(int to, int from);
  int size;
  std::vector<std::vector<byte> > parents;
};
