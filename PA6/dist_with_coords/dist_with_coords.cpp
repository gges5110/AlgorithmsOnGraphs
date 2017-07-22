#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <utility>
#include <cmath>
#include <algorithm> // std::reverse

using namespace std;

// See the explanations of these typedefs and constants in the starter for friend_suggestion
typedef vector<vector<vector<int>>> Adj;
typedef long long Len;

const Len const_INFINITY = numeric_limits<Len>::max() / 4;

class AStar {
  // See the descriptions of these fields in the starter for friend_suggestion
  uint32_t _n;
  Adj _adj, _cost;
  vector<vector<Len>> _distance;
  vector<vector<Len>> _fScore;
  vector<uint32_t> _workset;
  vector<vector<int32_t>> _prev;
  vector<bool> _visited;
  // Coordinates of the nodes
  vector<std::pair<Len, Len>> _xy;


  int extractMinFScore(int direction) const {
    Len min = const_INFINITY;
    int min_index = -1;
    for (uint32_t i = 0; i < _fScore[direction].size(); ++i) {
      if (!_visited[i] && min > _fScore[direction][i]) {
        min = _fScore[direction][i];
        min_index = i;
      }
    }

    return min_index;
  }

  // void printDistance(const vector<Len> &dist) const {
  //   for (uint32_t i = 0; i < dist.size(); ++i) {
  //     std::cout << "dist[" << i << "] = " << dist[i] << endl;
  //   }
  // }
  //
  // void printPath(const vector<uint32_t> &path) const {
  //   for (uint32_t i = 0; i < path.size(); ++i) {
  //     if (i != path.size() - 1) {
  //       std::cout << path[i] << " -> ";
  //     } else {
  //       std::cout << path[i] << endl;
  //     }
  //   }
  // }
  //
  // void printPrev(uint32_t direction) const {
  //   for (uint32_t i = 0; i < _prev[direction].size(); ++i) {
  //     if (i != _prev[direction].size() - 1) {
  //       std::cout << _prev[direction][i] << ", ";
  //     } else {
  //       std::cout << _prev[direction][i] << endl;
  //     }
  //   }
  // }

  Len calculateShortestPath(uint32_t s, uint32_t t) {
    Len min = const_INFINITY;
    uint32_t u_best;
    for (uint32_t u: _workset) {
      if (_distance[0][u] != const_INFINITY && _distance[1][u] != const_INFINITY) {
        int alt = _distance[0][u] + _distance[1][u];
        if (alt < min) {
          min = alt;
          u_best = u;
        }
      }
    }

    uint32_t last = u_best;
    vector<uint32_t> path;
    while (last != s) {
      path.push_back(last);
      last = _prev[0][last];
    }

    std::reverse(path.begin(), path.end());
    last = u_best;
    while (last != t) {
      if (last != u_best) {
        path.push_back(last);
      }
      last = _prev[1][last];
    }

    // printPath(path);

    return min == const_INFINITY ? -1 : min;
  }

  Len heuristic_estimate(uint32_t s, uint32_t t) const {
    return sqrt(pow(_xy[s].first - _xy[t].first, 2) + pow(_xy[s].second - _xy[t].second, 2));
  }

public:
  AStar(uint32_t n, const Adj &adj, const Adj &cost, const std::vector<std::pair<Len,Len>> &xy) :
    _n(n),
    _adj(adj),
    _cost(cost),
    _distance(2, vector<Len>(_n)),
    _fScore(2, vector<Len>(_n)), // fScore := map with default value of Infinity
    _prev(2, vector<int32_t>(_n)),
    _visited(_n),
    _xy(xy) {
    _workset.reserve(_n);
  }

  // See the description of this method in the starter for friend_suggestion
  void clear() {
    for (uint32_t v = 0; v < _n; ++v) {
      _distance[0][v] = _distance[1][v] = const_INFINITY;
      _prev[0][v] = _prev[1][v] = -1;
      _visited[v] = false;
      _fScore[0][v] = _fScore[1][v] = const_INFINITY;
    }
    _workset.clear();
  }

  // Returns the distance from s to t in the graph.
  Len query(uint32_t s, uint32_t t) {
    clear();

    if (s == t) {
      return 0;
    }

    uint32_t direction = 0;
    _distance[0][s] = 0;
    _distance[1][t] = 0;

    // fScore[start] := heuristic_estimate(start, goal)
    _fScore[0][s] = heuristic_estimate(s, t);
    _fScore[1][t] = heuristic_estimate(t, s);
    assert(_fScore[0][s] == _fScore[1][t]);

    while (true) {
      // Extract min based on potential instead of the actual distance.
      int u = extractMinFScore(direction);

      if (u == -1 || _visited[u]) {
        break;
      }

      for (uint32_t j = 0; j < _adj[direction][u].size(); ++j) {
        int v = _adj[direction][u][j];
        int alt = _distance[direction][u] + _cost[direction][u][j];
        if (alt < _distance[direction][v]) {
          // fScore[neighbor] := gScore[neighbor] + heuristic_estimate(neighbor, goal)
          _fScore[direction][v] = alt + heuristic_estimate(v, direction == 0 ? t : s);
          _prev[direction][v] = u;
          _distance[direction][v] = alt;
        }
      }

      _visited[u] = true;
      _workset.push_back(u);

      direction = !direction;
    }

    return calculateShortestPath(s, t);
  }
};


int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "Please provide a valid filename for testing." << std::endl;
  } else {
    ifstream fs;
    fs.exceptions(ifstream::failbit | ifstream::badbit);
    try {
      fs.open(argv[1]);

      // Original main
      uint32_t n, m;
      fs >> n >> m;

      std::vector<std::pair<Len,Len>> xy(n);
      for (uint32_t i = 0; i < n; ++i) {
        int a, b;
        fs >> a >> b;
        xy[i] = make_pair(a,b);
      }
      Adj adj(2, vector<vector<int>>(n));
      Adj cost(2, vector<vector<int>>(n));
      for (uint32_t i = 0; i < m; ++i) {
        uint32_t u, v, c;
        fs >> u >> v >> c;
        adj[0][u-1].push_back(v-1);
        cost[0][u-1].push_back(c);
        adj[1][v-1].push_back(u-1);
        cost[1][v-1].push_back(c);
      }

      AStar astar(n, adj, cost, xy);

      uint32_t t;
      fs >> t;
      for (uint32_t i = 0; i < t; ++i) {
        uint32_t u, v;
        fs >> u >> v;
        // std::cout << u << ", " << v << std::endl;
        std::cout << astar.query(u-1, v-1) << std::endl;
      }
    } catch (ifstream::failure& e) {
      std::cerr << "Exception opening/reading file" << std::endl;
    }
    fs.close();
  }
  return 0;
}
