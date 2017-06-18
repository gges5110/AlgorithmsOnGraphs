/*
Clustering
Problem Introduction
Clustering is a fundamental problem in data mining. The goal is to partition
a given set of objects into subsets (or clusters) in such a way that any two
objects from the same subset are close (or similar) to each other, while any
two objects from different subsets are far apart.

Problem Description
Task. Given n points on a plane and an integer k, compute the largest possible value of d such that the
given points can be partitioned into k non-empty subsets in such a way that the distance between any
two points from different subsets is at least d.
Input Format. The first line contains the number n of points. Each of the following n lines defines a point
(xi, yi). The last line contains the number k of clusters.
Constraints. 2 <= k <= n <= 200; -10^3 <= xi, yi <= 10^3 are integers. All points are pairwise different.
Output Format. Output the largest value of d. The absolute value of the difference between the answer of
your program and the optimal value should be at most 10􀀀6. To ensure this, output your answer with
at least seven digits after the decimal point (otherwise your answer, while being computed correctly,
can turn out to be wrong because of rounding issues).
*/

#include <algorithm> /* sort */
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cassert>
#include <vector>
#include <cmath> /*sqrt, pow*/
#include "UnionFind.h"

using std::vector;
using std::pair;
using std::ifstream;

template <typename T>
class Coordinate {
public:
  T x, y;
  Coordinate(T _x, T _y): x(_x), y(_y) {}
  Coordinate() {}
};

template <typename T>
T Eucledian_distance(const Coordinate<T> &p_1, const Coordinate<T> &p_2) {
  return sqrt(pow(p_1.x - p_2.x, 2) + pow(p_1.y - p_2.y, 2));
}

class Edge {
public:
  int v1, v2;
  double w;

  Edge(int _v1, int _v2, double _w) : v1(_v1), v2(_v2), w(_w) {}
  bool operator < (const Edge &that) const {
    return (this->w < that.w);
  }
};

class Kruskal {
public:
  int vertex_size;
  vector<Edge> edges;

  Kruskal(int vertex_size, const vector<Edge> &edges) : vertex_size(vertex_size), edges(edges) {}

  vector<Edge> MST() {
    return MST(0);
  }

  vector<Edge> MST(int k) {
    vector<Edge> T;

    // Sort the edges in order of increasing cost
    std::sort(edges.begin(), edges.end());

    UF union_find(vertex_size);

    for (Edge e: edges) {
      if (!union_find.find(e.v1, e.v2)) {
        T.push_back(e);
        union_find.unite(e.v1, e.v2);
      }
      if (T.size() == vertex_size - k) {
        break;
      }
    }
    return T;
  }
};

double clustering(const vector<int> &x, const vector<int> &y, int k) {
  int n = x.size();
  vector<Edge> edges;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      double d = Eucledian_distance(Coordinate<double>(x[i], y[i]), Coordinate<double>(x[j], y[j]));
      edges.push_back(Edge(i, j, d));
    }
  }
  Kruskal kruskal(n, edges);
  vector<Edge> T = kruskal.MST(k - 1);
  return T[T.size() - 1].w;
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
      int k;
      fs >> n;
      vector<int> x(n), y(n);
      for (size_t i = 0; i < n; i++) {
        fs >> x[i] >> y[i];
      }
      fs >> k;
      std::cout << std::setprecision(10) << clustering(x, y, k) << std::endl;
    } catch (ifstream::failure& e) {
      std::cerr << "Exception opening/reading file" << std::endl;
    }
    fs.close();
  }
  return 0;
}
