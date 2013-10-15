#include "dijkstra.h"
#include <queue>
#include <iostream>

Dijkstra::Dijkstra(const std::vector<std::vector<int> > &graph) :
  size(graph.size()),
  parents(size * size, 0) {
  // When all weights are one, the priority queue reduces to FIFO queue
  std::queue<int> queue;
  for (int origin = 1; origin <= int(graph.size()); origin++) {
    queue.push(origin);
    while (!queue.empty()) {
      int node = queue.front(); queue.pop();
      for (int neighbor = 1; neighbor <= int(graph.size()); neighbor++) {
	bool isNeighbor = false;
	for (auto nit = graph[neighbor-1].begin(); nit != graph[neighbor-1].end(); ++nit)
	  if (*nit == node) isNeighbor = true;
	if (!isNeighbor) continue;
	if (next(neighbor, origin) == 0) {
          next(neighbor, origin) = node;
	  //	  std::cout << "Best way to " << neighbor << " from " << origin << ": " << node << std::endl;
          queue.push(neighbor);
        }
      }
    }
  }
};

Dijkstra::byte &Dijkstra::next(int to, int from) {
  return parents[(to-1)*size + (from-1)];
};

int Dijkstra::next(int to, int from) const {
  return parents[(to-1)*size + (from-1)];
};
