#include "dijkstra.h"
#include <queue>

Dijkstra::Dijkstra(const std::vector<std::vector<int> > &graph) :
  size(graph.size()),
  parents(size * size, 0) {
  // When all weights are one, the priority queue reduces to FIFO queue
  std::queue<int> queue;
  for (int origin = 1; origin <= int(graph.size()); origin++) {
    queue.push(origin);
    while (!queue.empty()) {
      int node = queue.front(); queue.pop();
      for (auto nit = graph[node].begin(); nit != graph[node].end(); ++nit) {
        int neighbor = *nit;
        if (next(origin, neighbor) == 0) {
          next(origin, neighbor) = node;
          queue.push(neighbor);
        }
      }
    }
  }
};

Dijkstra::byte &Dijkstra::next(int from, int to) {
  return parents[(from-1) * size + (to-1)];
};

int Dijkstra::next(int from, int to) const {
  return parents[(from-1) * size + (to-1)];
};
