/*
g++ -o friend_suggestion.exe friend_suggestion.cpp -std=c++11
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <limits>
#include <utility>

using namespace std;

// External vector of size 2 - for forward and backward search.
// Internal 2-dimensional vector is vector of adjacency lists for each node.
typedef vector<vector<vector<int>>> Adj;

// Distances can grow out of int type
typedef long long Len;

// Vector of two priority queues - for forward and backward searches.
// Each priority queue stores the closest unprocessed node in its head.
typedef vector<priority_queue<pair<Len, int>,vector<pair<Len,int>>,greater<pair<Len,int>>>> Queue;

// https://stackoverflow.com/questions/35534478/including-algorithm-and-limits-causes-invalid-pure-specifier-compilation-e
const Len const_INFINITY = numeric_limits<Len>::max() / 4;

class Bidijkstra {
  // Number of nodes
  uint32_t _n;
  // Graph _adj[0] and _cost[0] correspond to the initial graph,
  // _adj[1] and _cost[1] correspond to the reversed graph.
  // Graphs are stored as vectors of adjacency lists corresponding
  // to nodes.
  // Adjacency list itself is stored in _adj, and the corresponding
  // edge costs are stored in _cost.
  Adj _adj;
  Adj _cost;
  // _distance[0] stores distances for the forward search,
  // and _distance[1] stores distances for the backward search.
  vector<vector<Len>> _distance;
  // Stores all the nodes visited either by forward or backward search.
  vector<int> _workset;
  // Stores a flag for each node which is True iff the node was visited
  // either by forward or backward search.
  vector<bool> _visited;

  int extractMin(uint32_t direction) {
    Len min = const_INFINITY;
    int min_index = -1;
    for (uint32_t i = 0; i < _distance[direction].size(); ++i) {
      if (!_visited[i] && min > _distance[direction][i]) {
        min = _distance[direction][i];
        min_index = i;
      }
    }

    return min_index;
  }

  void printDistance(const vector<Len> &dist) {
    for (uint32_t i = 0; i < dist.size(); ++i) {
      std::cout << "dist[" << i << "] = " << dist[i] << endl;
    }
  }

  // Initialize the data structures before new query,
  // clear the changes made by the previous query.
  void clear() {
    for (uint32_t v = 0; v < _n; ++v) {
      _distance[0][v] = _distance[1][v] = const_INFINITY;
      _visited[v] = false;
    }
    _workset.clear();
  }

  Len calculateShortestPath() {
    Len min = const_INFINITY;
    for (int u: _workset) {
      if (_distance[0][u] != const_INFINITY && _distance[1][u] != const_INFINITY) {
        int alt = _distance[0][u] + _distance[1][u];
        if (min > alt) {
          min = alt;
        }
      }
    }

    return min == const_INFINITY ? -1 : min;
  }

public:
  Bidijkstra(int n, const Adj &adj, const Adj &cost) :
    _n(n),
    _adj(adj),
    _cost(cost),
    _distance(2, vector<Len>(n)),
    _visited(n)
  { _workset.reserve(n); }

  // Returns the distance from s to t in the graph.
  Len query(int s, int t) {
    clear();
    Queue q(2);
    if (s == t) {
      return 0;
    }
    int direction = 0;
    _distance[0][s] = 0;
    _distance[1][t] = 0;

    // Implement the rest of the algorithm yourself
    while (true) {
      int u = extractMin(direction);

      if (u == -1 || _visited[u]) {
        break;
      } else {
        _visited[u] = true;
        _workset.push_back(u);
        for (uint32_t j = 0; j < _adj[direction][u].size(); ++j) {
          int v = _adj[direction][u][j];
          int alt = _distance[direction][u] + _cost[direction][u][j];
          if (alt < _distance[direction][v]) {
            _distance[direction][v] = alt;
          }
        }
      }

      direction = !direction;
    }

    return calculateShortestPath();
  }
};

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "Please provide a valid filename for testing." << std::endl;
  } else {
    std::ifstream fs;
    fs.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
      fs.open(argv[1]);

      // Original main
      int n, m;
      fs >> n >> m;
      Adj adj(2, vector<vector<int>>(n));
      Adj cost(2, vector<vector<int>>(n));
      for (int i = 0; i < m; ++i) {
        int u, v, c;
        fs >> u >> v >> c;
        adj[0][u-1].push_back(v-1);
        adj[1][v-1].push_back(u-1);

        cost[0][u-1].push_back(c);
        cost[1][v-1].push_back(c);
      }

      Bidijkstra bidij(n, adj, cost);

      int t;
      fs >> t;
      for (int i=0; i<t; ++i) {
        int u, v;
        fs >> u >> v;
        std::cout << bidij.query(u-1, v-1) << std::endl;
      }
    } catch (std::ifstream::failure& e) {
      std::cerr << "Exception opening/reading file" << std::endl;
    }
    fs.close();
  }
  return 0;
}
