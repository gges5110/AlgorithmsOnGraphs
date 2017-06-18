/*
Building Roads to Connect Cities
Problem Introduction
In this problem, the goal is to build roads between some pairs of the
given cities such that there is a path between any two cities and the
total length of the roads is minimized.
*/

#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cmath> /*sqrt, pow*/
#include <limits>
#include <unordered_set>

using std::vector;
using std::numeric_limits;
using std::ifstream;
using std::sqrt;
using std::pow;

template <typename T>
class Coordinate {
public:
  T x, y;
  Coordinate(T _x, T _y): x(_x), y(_y) {}
  Coordinate() {}
};

double Eucledian_distance(const Coordinate<double> &p_1, const Coordinate<double> &p_2) {
  return sqrt(pow(p_1.x - p_2.x, 2) + pow(p_1.y - p_2.y, 2));
}

int find_min(const std::unordered_set<int> &Q, const vector<double> &key) {
  int min_id = numeric_limits<int>::max();
  double min = numeric_limits<double>::max();

  for (int id: Q) {
    if (key[id] < min) {
      min_id = id;
      min = key[id];
    }
  }

  return min_id;
}

double minimum_distance(const vector<int> &x, const vector<int> &y) {
  double result = 0.;
  int n = x.size();
  // Construct 2D matrix for distance
  vector<vector<double>> dist(n, vector<double>(n, 0));
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      double d = Eucledian_distance(Coordinate<double>(x[i], y[i]), Coordinate<double>(x[j], y[j]));
      dist[i][j] = d;
      dist[j][i] = d;
    }
  }

  //
  vector<double> key(n, numeric_limits<double>::max());
  vector<int> parent(n, -1);

  key[0] = 0;
  std::unordered_set<int> Q;
  for (int i = 0; i < n; ++i)
    Q.insert(i);

  int iteration = 0;
  while (!Q.empty()) {
    // Find the min(Q) by key value
    int u = find_min(Q, key);
    Q.erase(u);
    if (parent[u] != -1) {
      result += dist[u][parent[u]];
    }

    for (int v = 0; v < n; ++v) {
      if (dist[u][v] != 0) {
        auto search = Q.find(v);
        if (search != Q.end() && dist[u][v] < key[v]) {
          parent[v] = u;
          key[v] = dist[u][v];
        }
      }
    }
  }

  return result;
}


int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "Please provide a valid filename for testing." << std::endl;
  } else {
    ifstream fs;
    fs.exceptions(ifstream::failbit | ifstream::badbit);
    try {
      fs.open(argv[1]);

      // Original main
      size_t n;
      fs >> n;
      vector<int> x(n), y(n);
      for (size_t i = 0; i < n; i++) {
        fs >> x[i] >> y[i];
      }
      std::cout << std::setprecision(10) << minimum_distance(x, y) << std::endl;
    } catch (ifstream::failure& e) {
      std::cerr << "Exception opening/reading file" << std::endl;
    }
    fs.close();
  }
  return 0;
}
