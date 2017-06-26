
#include <iostream>
#include <fstream>
#include <vector>
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

const Len INFINITY = numeric_limits<Len>::max() / 4;

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

public:
  Bidijkstra(int n, Adj adj, Adj cost)
    : n_(n), adj_(adj), cost_(cost), distance_(2, vector<Len>(n, INFINITY)), visited_(n)
  { workset_.reserve(n); }

  // Initialize the data structures before new query,
  // clear the changes made by the previous query.
  void clear() {
    for (int i = 0; i < workset_.size(); ++i) {
      int v = workset_[i];
      distance_[0][v] = distance_[1][v] = INFINITY;
      visited_[v] = false;
    }
    workset_.clear();
  }

  // Processes visit of either forward or backward search
  // (determined by value of side), to node v trying to
  // relax the current distance by dist.
  void visit(Queue& q, int side, int v, Len dist) {
    // Implement this method yourself
  }

  // Returns the distance from s to t in the graph.
  Len query(int s, int t) {
    clear();
    Queue q(2);
    visit(q, 0, s, 0);
    visit(q, 1, t, 0);
    // Implement the rest of the algorithm yourself

    return -1;
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
