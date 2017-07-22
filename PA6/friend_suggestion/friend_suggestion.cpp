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
const Len INFINITY_ = numeric_limits<Len>::max() / 4;

class Bidijkstra {
  // Number of nodes
  int n_;
  // Graph adj_[0] and cost_[0] correspond to the initial graph,
  // adj_[1] and cost_[1] correspond to the reversed graph.
  // Graphs are stored as vectors of adjacency lists corresponding
  // to nodes.
  // Adjacency list itself is stored in adj_, and the corresponding
  // edge costs are stored in cost_.
  Adj adj_;
  Adj cost_;
  // distance_[0] stores distances for the forward search,
  // and distance_[1] stores distances for the backward search.
  vector<vector<Len>> distance_;
  // Stores all the nodes visited either by forward or backward search.
  vector<int> workset_;
  // Stores a flag for each node which is True iff the node was visited
  // either by forward or backward search.
  vector<bool> visited_;

  int extractMin(const vector<Len> &dist, const vector<bool> &visited) {
    int min = numeric_limits<int>::max(), min_index = -1;
    for (int i = 0; i < dist.size(); ++i) {
      if (!visited[i] && min > dist[i]) {
        min = dist[i];
        min_index = i;
      }
    }

    return min_index;
  }

  bool inside(const vector<int> &v, int u) const {
    return std::find(v.begin(), v.end(), u) != v.end();
  }

  void printDistance(const vector<Len> &dist) {
    for (int i = 0; i < dist.size(); ++i) {
      std::cout << "dist[" << i << "] = " << dist[i] << endl;
    }
  }

  // Initialize the data structures before new query,
  // clear the changes made by the previous query.
  void clear() {
    for (int i = 0; i < workset_.size(); ++i) {
      int v = workset_[i];
      distance_[0][v] = distance_[1][v] = INFINITY_;
      visited_[v] = false;
    }
    workset_.clear();
  }

  Len calculateShortestPath() {
    Len min = INFINITY_;
    for (int u: workset_) {
      if (distance_[0][u] != INFINITY_ && distance_[1][u] != INFINITY_) {
        int alt = distance_[0][u] + distance_[1][u];
        if (min > alt) {
          min = alt;
        }
      }
    }

    return min == INFINITY_ ? -1 : min;
  }

public:
  Bidijkstra(int n, Adj adj, Adj cost)
    : n_(n), adj_(adj), cost_(cost), distance_(2, vector<Len>(n, INFINITY_)), visited_(n)
  { workset_.reserve(n); }

  // Returns the distance from s to t in the graph.
  Len query(int s, int t) {
    clear();
    Queue q(2);
    if (s == t) {
      return 0;
    }
    int direction = 0;
    distance_[0][s] = 0;
    distance_[1][t] = 0;

    // Implement the rest of the algorithm yourself
    while (true) {
      int u = extractMin(distance_[direction], visited_);

      if (inside(workset_, u) || u == -1) {
        break;
      } else {
        visited_[u] = true;
        workset_.push_back(u);
        for (int j = 0; j < adj_[direction][u].size(); ++j) {
          int v = adj_[direction][u][j];
          int alt = distance_[direction][u] + cost_[direction][u][j];
          if (alt < distance_[direction][v]) {
            distance_[direction][v] = alt;
          }
        }
      }

      direction = direction == 0 ? 1 : 0;
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
